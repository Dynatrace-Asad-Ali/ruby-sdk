require 'rake/extensiontask'
require 'rubygems/package_task'

##
# Rake::ExtensionTask comes from the rake-compiler and understands how to
# build and cross-compile extensions.
#
# See https://github.com/luislavena/rake-compiler for details

Rake::ExtensionTask.new 'oneagent_sdk' do |ext|

  # This causes the shared object to be placed in lib/oneagent_sdk/oneagent_sdk.so
  #
  # It allows lib/oneagent_sdk.rb to load different versions if you ship a
  # precompiled extension that supports multiple ruby versions.

  ext.lib_dir = 'lib/oneagent_sdk'
end

s = Gem::Specification.new 'oneagent_sdk', '1.0' do |s|
  s.summary = 'Dynatrace OneAgentSDK Binding for Ruby'
  s.description = "A binding for Ruby to the Native Dynatrace OneAgentSDK"
  s.license = "MIT"
  s.homepage = "https://www.dynatrace.com"
  s.authors = ["Reinhard Pilz", "Asad Ali"]
  s.email = ["reinhard.pilz@dynatrace.com", "asad.ali@dynatrace.com"]

  # this tells RubyGems to build an extension upon install

  s.extensions = %w[ext/oneagent_sdk/extconf.rb]

  # naturally you must include the extension source in the gem

  s.files = %w[
    MIT-LICENSE
    Rakefile
    ext/oneagent_sdk/extconf.rb
    ext/oneagent_sdk/oneagent_sdk.c
	ext/oneagent_sdk/include/onesdk.h
	ext/oneagent_sdk/include/onesdk_agent.h
	ext/oneagent_sdk/include/onesdk_common.h
	ext/oneagent_sdk/include/onesdk_config.h
	ext/oneagent_sdk/include/onesdk_init.h
	ext/oneagent_sdk/include/onesdk_msvc.h
	ext/oneagent_sdk/include/onesdk_string.h
	ext/oneagent_sdk/lib/x86_64-linux/libonesdk_static.a
    lib/oneagent_sdk.rb
	lib/oneagent_sdk/oneagent_sdk.so
  ]
end

# The package task builds the gem in pkg/oneagent_sdk-1.0.gem so you can test
# installing it.

Gem::PackageTask.new s do end

# This isn't a good test, but does provide a sanity check

task test: %w[compile] do
  ruby '-Ilib', '-roneagent_sdk', '-e', 'p OneAgentSdk.new(5).free'
end

task default: :test

