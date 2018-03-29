# tcp_server.rb
require 'socket'
require 'oneagent_sdk'

puts OneAgentSdk.initialize
tracer=OneAgentSdk.incomingremotecalltracer_create("getData", "/", "localhost/sample1/input_processor")
puts tracer
server = TCPServer.new 8080

while session = server.accept
  puts OneAgentSdk.tracer_start(tracer)
  session.puts "Hello world! The time is #{Time.now}"
  dbtracer = OneAgentSdk.databaseinfo_create("Employee", "Oracle", "test", "test")
  OneAgentSdk.databaserequesttracer_create_sql(dbtracer, "select * from employee")
  session.close
  OneAgentSdk.tracer_end(tracer)
end
OneAgentSdk.shutdown
