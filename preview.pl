#!/usr/bin/perl

use Tk;
use Tk::JPEG;
use strict;
use warnings;






my @file_names;

for my $fn (@ARGV) {
    push @file_names, (glob($fn));
}

my $fmt;

my $mw = MainWindow->new(-title=>"Image Previewer", -width=>800,-height=>800);
my $lbl = $mw->Label(-width=>800,-height=>800)->pack();

my $curImg = pop @file_names;
    if ($curImg =~ /\.jpg$/i) {
	$fmt = 'jpeg';
    }
my $image = $mw->Photo('-format' => $fmt, -file=>$curImg);
$lbl->configure(-image=>$image);

sub acceptCurImage {
    print "Accepted image $curImg!";
    $curImg = pop @file_names;
    if ($curImg =~ /\.jpg$/i) {
	$fmt = 'jpeg';
    }
    $image = $mw->Photo('-format' => $fmt, -file=>$curImg);
    $lbl->configure(-image=>$image);
}

sub rejectCurImage {
    print "Accepted image $curImg!";
    $curImg = pop @file_names;
    if ($curImg =~ /\.jpg$/i) {
	$fmt = 'jpeg';
    }
    $image = $mw->Photo('-format' => $fmt, -file=>$curImg);
    $lbl->configure(-image=>$image);
}


$lbl->bind('<1>' => \&acceptCurImage);
$lbl->bind('<3>' => \&rejectCurImage);

MainLoop;
