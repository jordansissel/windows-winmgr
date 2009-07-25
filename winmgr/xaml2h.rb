# ruby
#

lines = File.open(ARGV[0]).readlines()

defname = ARGV[0].upcase.gsub(".","_")
File.open(ARGV[1], "w") do |out|
  out.puts "#pragma once"
  out.puts "#define #{defname} \\"
  lines.each do |line|
    line = line.gsub("\"", "\\\"").chomp
    out.puts "\"#{line}\" \\"
  end

  out.puts ""
  out.puts 
end

