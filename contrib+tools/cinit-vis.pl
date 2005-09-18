#!/usr/bin/perl -w
# (c) by Marcus Przyklink (downhill-clinux@burningchaos.org)
# written for cinit and published under GPL
# beautified a bit by Nico Schottelius
# Version: 0.1


#
# Variables for location and output
#
# cinit-directory
my $path = "/etc/cinit/";
# started profile
my $starting_point = "init";
# the spaces for each level
my $space = "\ \ \ ";
# marker for need
my $need = "-->";
# marker for want
my $want = "==>";

#
# main function, recursively list the components of the cinit system
#
if (@ARGV) {
   if( $ARGV[0] =~ /-(h|-help)/ ) {
      print "Usage: Without parameters for standard-use (check variables in file)\n";
      print "       Parameters:\n";
      print "       -h for this help\n";
      print "       profile-name for a profile\n";
      exit(0);
   }
   else {
      $starting_point = $ARGV[0];
   }
}

#
# start first instance
# 
sub get_deeper {
   my ($point,$tmp_counter,$need_want) = @_;
   my $pointer;
   if( $need_want eq "n" ) {
      $pointer = $need;
   }
   else {
      $pointer = $want;
   }
   print $space x $tmp_counter, $pointer, "\ ", $point, "\n";
   opendir(DIR, "${path}${point}/needs");
   my @next_need = sort grep(!/^\./, readdir(DIR)) and
   closedir(DIR);
   opendir(DIR, "${path}${point}/wants") and
   my @next_want = sort grep(!/^\./, readdir(DIR)) and
   closedir(DIR);
   if( @next_need ) {
      foreach $thing (@next_need) {
         get_deeper($thing,$tmp_counter+1,"n");
      }
   }
   if( @next_want ) {
      foreach $thing (@next_want) {
         get_deeper($thing,$tmp_counter+1,"w");
      }
   } 
}

#
# start first instance
# 
get_deeper($starting_point,0,"n");

#
# work done, go home
#
exit(0);
