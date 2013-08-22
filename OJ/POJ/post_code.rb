require "net/http"
#require 'mechanize'

=begin
url = URI.parse('http://poj.org/login?B1=login&password1=123456&url=%2Fregister&user_id1=submittersubmitter')
response=Net::HTTP.get(url)
#,{'B1'=>"login",'password1'=>'bbc_1029384756','url'=>'/','usr_id1'=>'footoredo'}
puts response

code=""
File.open("tp.cpp") do |file|
	file.each_line{|line| code+=line}
end

url = URI.parse('http://poj.org/submit')
response = Net::HTTP.post_form(url,{'language'=>4,'problem_id'=>1000,'source'=>code,'submit'=>'submit'})
puts response.body;
=end
=begin
cookie = Mechanize::Cookie.new("JSESSIONID", "7A06143C45A75AA8EE2597A742649A39")
cookie.domain = "poj.org"
cookie.path = "/"

agent = Mechanize.new
agent.cookie_jar.add!(cookie)
page = agent.get('http://poj.org/submit')
puts page.body
=end

uri = URI('http://poj.org/searchproblem')
cookie="JSESSIONID=7A06143C45A75AA8EE2597A742649A39"
data = {
	'B1'=>'GO',
	'field'=>'Title',
	'key'=>'shit'
}
#response = http.post(uri.path,data,headers)
#puts response.body
req = Net::HTTP::Post.new(uri.path)
req.set_form_data(data)
req['Cookie']=cookie;

res=Net::HTTP.start(uri.hostname, uri.port) do |http|
	http.request(req)
end

puts res.body