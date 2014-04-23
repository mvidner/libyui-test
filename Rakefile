# -*- coding: utf-8 -*-
# make continuous integration using rubygem-packaging_rake_tasks
# Copyright (C) 2014 SUSE LLC
# MIT license

require "packaging/tasks"
require "packaging/configuration"

ENV["LIMIT"] = "20" # line count limit for "too short to need a license"
# skip 'tarball' task, it's redefined here
Packaging::Tasks.load_tasks(:exclude => ["tarball.rake"])

Packaging.configuration do |conf|
  if ENV["LIBYUI_SUBMIT"] == "SLES"
    conf.obs_api        = "https://api.suse.de/"
    conf.obs_project    = "Devel:YaST:Head"
    conf.obs_target     = "SLE-12"
    conf.obs_sr_project = "SUSE:SLE-12:GA"
  else
    conf.obs_project    = "devel:libraries:libyui"
    conf.obs_sr_project = "openSUSE:Factory"
  end
  # Used by osc:* tasks
  # One of libyui-test-{ncurses,qt,gtk}
  conf.package_name = ENV["PACKAGE"]
  conf.version      = `sed -n 's/VERSION = //;T;p;q' Makefile`.chomp
end

desc 'Pretend to run the test suite'
task :test do
  puts 'No tests yet' if verbose
end

desc 'Build a tarball for OBS'
task :tarball do
  sh "make dist"
end
