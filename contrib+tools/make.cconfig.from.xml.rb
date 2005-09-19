#!/usr/bin/env ruby

=begin

    Create a cconfig directory based on a xml input.
    (C) 2005 by René Nussbaumer aka KillerFox

    This script is written for the clinux-System and published
    under the terms of GPL 2.0

    Version: 0.3

    ChangeLog:
        Version 0.3 (René Nussbaumer):
        * Added binary file support
        * Added sha1 checksum for binary files
    
        Version 0.2 (René Nussbaumer):
        * Added some commandline options
        * Added «level» so control the restrictivity of the program
        * Added more «intelligence» to the program, to detect internal broken dependcies.
        * Support «debug»-Levels.
        * Print statistic at the end of the programs about warnings and errors.
        
        Version 0.1 (René Nussbaumer):
        * Initial

    Todo:
        * Use an rexml alternative
        * Some cleanup
        * Optimize
        * Testing?

    Features:
        * Create a cconfig directory based on a xml

=end

require 'rexml/document'
require 'getoptlong'
require 'base64'
require 'digest/sha1'

@verbose   = 0
@level     = 1
@version   = '0.3'

@warnings  = 0
@errors    = 0
@checklist = Array.new

def printMsg(prefix, msg)
    puts '%-12s %s' % [prefix + ':', msg]
end

def error(msg, fatal = 0)
    @errors += 1
    fatal = 0 if(@level < 1)
    fatal = 255 if(@level > 1 && !fatal)
    printMsg(fatal != 0 ? 'PANIC' : 'ERROR', msg)
    Kernel.exit(-fatal) if(fatal != 0)
end

def warn(msg)
    error(msg, 1) if(@level > 1)
    @warnings += 1
    printMsg('WARNING', msg)
end

def info(msg)
    printMsg('INFO', msg)
end

def debug(msg, verbosity = 1)
    if(@verbose >= verbosity)
        printMsg("DEBUG(#{verbosity})", msg)
    end
end

def createObject(name)
    error("#{name} already exists.", 1) if(FileTest.exists?(name))
    begin
        Dir.mkdir(name)
    rescue
        error("Could not create directory #{name}: #{$!}. Abort.", 7)
    end
    debug("Object #{File.expand_path(name)} has been created.", 4)
end

def createAttribute(name, content = nil)
    warn("#{name} already exists. Overwrite.") if(FileTest.exists?(name))
    begin
        file = File.new(name, 'w')
        file.print content if(content && !content.empty?)
        file.close
        debug("Attribute #{File.expand_path(name)} has been created", 4)
    rescue
        error("Could not create file #{name}: #{$!}. Skipped.")
    end
end

def createLink(name, target, type)
    warn("#{name} already exists. Overwrite.") if(FileTest.exists?(name))
    error("Broken dependencies! Please take a look if #{target} exists on your system", 2) if(type == 'external' && !FileTest.exists?(target))
    if(!FileTest.exists?(target) && type != 'external')
        #info("Possible break. But maybe the target #{target} does not yet exists. Checking later.") 
        exptarget = File.expand_path(target)
        @checklist << exptarget
        debug("Adding #{target} to the list of internal dependcies to check.", 2)
    end
    begin
        error('You\'ve a system which does not support symbolic links. Abort.', 3) if(File.symlink(target, name) != 0)
    rescue
        error("Could not create symlink #{name} => #{target}: #{$!}.", 3)
    end
    debug("Link #{File.expand_path(name)} has been created", 4)
end

def doWork(elm)
    name = elm.name
    attrname = elm.attributes['name']
    error("XML Tag with missing name attribute!", 5) if(!attrname)
    if(name =~ /(object|cconfig)/)
        if(name == 'cconfig')
            if(elm.attributes['version'])
                info("Found a version string: #{elm.attributes['version']}")
                warn("This XML is maybe incompatible with this programm. I'm a version #{@version} script. The XML is generated with a version #{elm.attributes['version']} script. Please update.") if(elm.attributes['version'] > @version)
            end
        end
        createObject(attrname)
        if(elm.has_elements?)
            pwd = Dir.pwd
            Dir.chdir(attrname)
            elm.each_element { |e|
                doWork(e)
            }
            Dir.chdir(pwd)
        end
    elsif(name == 'attribute')
        text = nil
        e    = nil
        text = e.value if((e = elm.get_text))
        if(text && elm.attributes['type'] && elm.attributes['type'] == 'binary')
            text = Base64.decode64(text)
            if(Digest::SHA1.hexdigest(text) != elm.attributes['sha1'])
                warn("SHA1 differs from file: #{Dir.pwd}#{attrname}")
            end
        end
        createAttribute(attrname, text)
    elsif(name == 'link')
        error("link-Tag without content.", 6) if(!elm.has_text?)
        error("link with missing target. Skipped.") if(!elm.attributes['target'])
        createLink(attrname, elm.get_text.value, elm.attributes['target'])
    end
end

puts "This is #{File.basename(__FILE__)} v#{@version} by René Nussbaumer"
puts

opts = GetoptLong.new(
    ['--verbose', '-v', GetoptLong::OPTIONAL_ARGUMENT],
    ['--level',   '-l', GetoptLong::REQUIRED_ARGUMENT],
    ['--version', '-V', GetoptLong::NO_ARGUMENT]
)

opts.each { |arg,value|
    case arg
    when '--verbose'
        @verbose += 1
        value.each_byte { |x|
            if(x.chr == 'v')
                @verbose += 1
            end
        }
        debug("Verbosity set to: #{@verbose}")
    when '--level'
        debug("Setting level to: #{value}", 3)
        case value
        when 'low'
            @level = 0
        when 'normal'
            @level = 1
        when 'paranoid'
            @level = 2
        else
            warn('Unknown level: ' + value)
        end
    when '--version'
        Kernel.exit(0)
    else
        warn("Unknown option #{arg}#{value && !value.empty? ? ('with value ' + value) : ''}")
    end
}

if(!ARGV[0])
    puts 'Need at least one argument'
    puts "Usage: #{__FILE__} <xml file|->"
    Kernel.exit(1)
end


filedesc = $stdin

if(ARGV[0] != '-')
    filedesc = File.new(ARGV[0])
end

doc = REXML::Document.new filedesc

doWork(doc.root)

if(!@checklist.empty?)
    info('Now checking all broken internal dependcies again')
    broken = 0
    @checklist.each { |path|
        debug("Checking #{path}.", 2)
        if(!FileTest.exists?(path))
            broken += 1
            warn("Broken dependcies. #{path} does not exist. Please fix.")
        end
    }
    info('Looks good.') if(broken == 0)
    info('Bad, bad.')   if(broken > 0)
end

info("Successed. #{@warnings} warnings, #{@errors} errors")

