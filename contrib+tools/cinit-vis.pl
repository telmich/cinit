#!/usr/bin/perl -w
# (c) by Marcus Przyklink (downhill-clinux@burningchaos.org)
# written for cinit and published under GPL
# beautified a bit by Nico Schottelius
# optimized by René Nussbaumer
# Version: 0.1

use strict;
use warnings;

#
# Variables for location and output
#
# cinit-directory
my $path = "/etc/cinit/svc/";
# started profile
my $starting_point = "init";
# the spaces for each level (integer: amount of spaces)
my $space = 3;
# marker for need
my $need = "-->";
# marker for want
my $want = "==>";

#
# main function, recursively list the components of the cinit system
#
if (@ARGV) {
   if( $ARGV[0] =~ /-(h|-help)/ ) {
      print "Usage: " . __FILE__ . " without parameters for standard-use (check variables in file)\n";
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
   my ($point, $tmp_counter, $need_want) = splice @_;

   print " " x ($space * $tmp_counter) . ($need_want ? $need : $want) . " " . $point . "\n";

   opendir(DIR, "${path}${point}/needs") and
   my @next_need = sort grep(!/^\./, readdir(DIR)) and
   closedir(DIR);
   opendir(DIR, "${path}${point}/wants") and
   my @next_want = sort grep(!/^\./, readdir(DIR)) and
   closedir(DIR);

   for(@next_need) {
     get_deeper($_, $tmp_counter + 1, 1);
   }
   for(@next_want) {
     get_deeper($_, $tmp_counter + 1, 0);
   }
}

#
# start first instance
# 
get_deeper($starting_point, 0, 0);

#
# work done, go home
#
exit(0);
