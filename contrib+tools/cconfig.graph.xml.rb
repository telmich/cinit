#!/usr/bin/env ruby

=begin

    Writes an XML-Tree for a cconfig directory
    Idea by Nico Schottelius aka telmich
    Implemented and (C) by René Nussbaumer aka KillerFox

    This script is written for the clinux-System and published
    under the terms of GPL 2.0

    Version: 0.3

    ChangeLog:
        Version 0.3 (René Nussbaumer):
        * Added support for binary files
        * Added sha1 checksum for binary files
    
        Version 0.2 (René Nussbaumer):
        * Changed checking order: symlink, directory, file. Because of
          a logical bug -> directory follows symlink so, when a symlink
          points to a directory no «link» element is created.
    
        Version 0.1 (René Nussbaumer):
        * Holy hack for directory scanning (needs to be optimized)
        * Hack for rexml to print out «lost» tags. This rexml sux.

    Todo:
        * Optimize scanning.
        * Use another xml library instead of rexml crap.
          Problem: Produce dependencies -> no std-lib

    Features:
        * Create a flat (no deepnes without directory) and 1:1 image 
          of an cconfig directory

=end

require 'rexml/document'
require 'base64'
require 'digest/sha1'

require 'filemagic'

@version = '0.3'

def determineTarget(entry)
    return 'external'  if(!File.expand_path(entry).index(@initpath))
    return 'link'      if(FileTest.symlink?(entry))
    return 'object'    if(FileTest.directory?(entry))
    return 'attribute' if(FileTest.file?(entry))
    return 'unknown' # Should never be reached
end

def createTree(dir, parent)
    dir.each { |entry|
        next if(entry =~ /^(\.|\.\.)$/)

        if(FileTest.symlink?(entry))
            e = parent.add_element('link')

            # Much fun with links
            e.add_attributes( { 'name' => entry, 'target' => determineTarget(File.readlink(entry)) } )
            e.add_text(File.readlink(entry))
        elsif(FileTest.directory?(entry))
            e = parent.add_element('object')
            e.add_attribute('name', entry)

            # Bad, that we need to change the directory every time.
            oldPwd = Dir.pwd
            Dir.chdir(entry)
            createTree(Dir.new('.'), e)
            Dir.chdir(oldPwd)
        elsif(FileTest.file?(entry))
            e = parent.add_element('attribute')
            e.add_attribute('name', entry)
            if(File.stat(entry).size?)
                # Yeah, we got one WITH content! W00h00, let's party.

                fm = FileMagic.new(FileMagic::MAGIC_MIME)
                if(fm.file(entry) =~ /executable/)
                    e.add_attribute('type', 'binary')
                    text = File.new(entry).read
                    e.add_attribute('sha1', Digest::SHA1.hexdigest(text))
                    e.add_text(Base64.encode64(text))
                else
                    e.add_text(File.new(entry).read)
                end
                fm.close()
            end
        end
    }
end


if(!ARGV[0] || !FileTest.directory?(ARGV[0]))
    puts 'You need to specify a directory'
    Kernel.exit(-1)
end

doc = REXML::Document.new

e = doc.add_element('cconfig')
e.add_attribute('name', File.basename(ARGV[0]))
e.add_attribute('version', @version)

@initpath = File.expand_path(ARGV[0])
Dir.chdir(ARGV[0])
createTree(Dir.new('.'), doc.root)

out = ''
doc.write(out, 0, false, true)

REXML::XMLDecl.new('1.0', 'utf-8').write($stdout) # This should automatically printed by rexml. Damn bugs.
puts ''
puts out # Workaround for a buggy rexml

