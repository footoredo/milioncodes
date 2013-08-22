require 'net/http'

def my_post(uri,data)
	cookie = "PHPSESSID=91bb6b2p08fm2mm0ob2i54uqa5"
	req = Net::HTTP::Post.new(uri.path)
	req.set_form_data(data)
	req['Cookie']=cookie;

	res=Net::HTTP.start(uri.hostname, uri.port) do |http|
		http.request(req)
	end
	res
end

def search(key)
	uri = URI('http://www.lydsy.com/JudgeOnline/problemset.php?search='+key)
	Net::HTTP.get(uri)
end

def get_run_id(id,language=1)
	uri = URI('http://www.lydsy.com/JudgeOnline/status.php?problem_id='+id.to_s+
		'&user_id=submittersubmitter&language='+language.to_s)
	status=Net::HTTP.get(uri)
#puts status
	/\d+/.match(/<td>\d{5,}<td>/.match(status).to_s).to_s.to_i
end

def submit(id,path,language=1)
	code=""
	File.open(path) do |file|
		file.each_line{|line| code+=line}
	end

	uri = URI('http://www.lydsy.com/JudgeOnline/submit.php')
	data = {
		'id'=>id,
		'language'=>language,
		'source'=>code
	}
	my_post(uri,data)
	get_run_id(id,language)
end

def get_status(name,res)
	return "N/A" unless (res=~/#{name}:[a-zA-Z0-9 ]/)
	tr=/#{name}:[a-zA-Z0-9_ ]{4,}/.match(res).to_s
	tr["#{name}:"]=""
	tr
end

def trace_status(id)
	http=Net::HTTP.new('www.lydsy.com')
	cookie = "PHPSESSID=91bb6b2p08fm2mm0ob2i54uqa5"
	uri = URI('http://www.lydsy.com/JudgeOnline/showsource.php?id='+id.to_s)
	#data = 'solution_id='+id.to_s
	headers = { 'Cookie'=>cookie }
	res=http.get(uri,headers).body
#puts(status)
	status={}
	status[:result]=get_status('Result',res)
	status[:memory]=get_status('Memory',res)
	status[:time]=get_status('Time',res)
	status
end

#puts search("card")
#puts submit(1000,"tp.cpp")
#puts get_run_id(1000)
puts trace_status(470092)
