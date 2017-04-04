dir = ["quanguo", "beijing", "shanghai", "shenzhen", "guangzhou"]

p "fetching html starts..."
dir_num = Hash.new

for name in dir
    dir_num["#{name}"] = "song"
end

dir_num.each do |key, val|
  p key + " " + val
end
