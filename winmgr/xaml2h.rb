# ruby
#

lines = File.open(ARGV[0]).readlines()

puts ARGV.inspect
name = ARGV[0].split("\\")[-1]
defname = name.upcase.gsub(".","_")
outname = "#{ARGV[1]}\\#{name.split(".")[0]}.h"
puts "Converting #{name} -> #{outname}"
File.open(outname, "w") do |out|
  out.puts "#pragma once"
  out.puts "#define #{defname} \\"
  lines.each do |line|
    line = line.gsub("\"", "\\\"").chomp
    out.puts "\"#{line}\" \\"
  end

  out.puts ""
  out.puts 
end
puts "Done"
