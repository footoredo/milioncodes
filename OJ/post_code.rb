require "net/http"

code=""
File.open("tp.cpp") do |file|
	file.each_line{|line| code+=line}
end

url = URI.parse('http://acm.hdu.edu.cn/submit.php?action=submit')
response = Net::HTTP.post_form(url,{'check'=>0, 'language'=>'0', 'problemid'=>4576,'content'=>code})
puts response.body;