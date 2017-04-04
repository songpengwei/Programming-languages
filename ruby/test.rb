#!/bin/usr/env ruby
# coding : gbk
#tag_divide.rb
#################################

require 'iconv'
require 'hpricot'
require 'readline'
require 'fileutils'

tag = Hash.new

["ab", "cd"].each do |item1|
  tag[item1] = "accident"
end

["ef","gh"].each do |item2|
  tag[item2] = "traffic"
end

["ij", "kl"].each do |item3|
  tag[item3] = "weather"
end

p tag

file_hash = Hash.new
file_hash = {"accident" => $accident, "traffic" => $traffic, "weather" => $weather}

p file_hash

file_hash.each do |key, value|
  value = File.open("#{ARGV[0]}_#{key}","w+")
  p key
  p value
end

p "outside_block"
p file_hash["accident"]


file = File.open("#{ARGV[0]}", "r")
while line = file.gets
  if line.start_with?("http://")
	news = Array.new
	news << line
	while (line = file.gets) && !(line.start_with?("http://"))
	  news << line
	end
	title = news[1]
	tag.each do |key, value|
	  if title.include? "#{key}"
		news.each do |line|
		  file_hash[value].puts("#{line}")
		end
	  end
	  #p value
	  #p file_hash[value]
	end

  end
end

file_hash.each_value do |value|
  value.close
end 



