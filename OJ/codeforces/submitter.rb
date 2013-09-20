require 'net/http'

def my_post(uri,data)
	cookie = "JSESSIONID=02BA22E9C769A3D4A82C8A0D81ABEB66-n1"
	req = Net::HTTP::Post.new(uri.path)
	req.set_form_data(data)
	req['Cookie']=cookie;

	res=Net::HTTP.start(uri.hostname, uri.port) do |http|
		http.request(req)
	end
	res
end

def my_get(uri,data)
	cookie = "JSESSIONID=02BA22E9C769A3D4A82C8A0D81ABEB66-n1"
	req = Net::HTTP::Get.new(uri.path)
	req.set_form_data(data)
	req['Cookie']=cookie;

	res=Net::HTTP.start(uri.hostname, uri.port) do |http|
		http.request(req)
	end
	res
end

def search(key,field='Title')
	uri = URI('http://poj.org/searchproblem')
	data = {
		'B1'=>'GO',
		'field'=>field,
		'key'=>key
	}
	my_post(uri,data)
end

def get_run_id(id,language=0)
	uri = URI('http://poj.org/status?problem_id='+id.to_s+
		'&user_id=submittersubmitter&language='+language.to_s)
	status=Net::HTTP.get(uri)
#puts status
	/\d+/.match(/<tr align=center><td>\d+<\/td>/.match(status).to_s).to_s.to_i
end

def submit(id,path,language=0)
	code=""
	File.open(path) do |file|
		file.each_line{|line| code+=line}
	end

	uri = URI('http://poj.org/submit')
	data = {
		'language'=>language,
		'problem_id'=>id,
		'source'=>code,
		'submit'=>'Submit'
	}
	my_post(uri,data)
	get_run_id(id,language)
end

def get_status(name,res)
	tr=/#{name}.+<\/td>/.match(res)
	tr=/>[a-zA-Z0-9 \/]{4,}</.match(tr.to_s)
	/[a-zA-Z0-9 \/]{4,}/.match(tr.to_s)
end

def trace_status(id)
	http=Net::HTTP.new('poj.org')
	cookie = "JSESSIONID=02BA22E9C769A3D4A82C8A0D81ABEB66-n1"
	uri = URI('http://poj.org/showsource?solution_id='+id.to_s)
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

puts search("shit").body
#puts submit(1000,"tp.cpp")
#puts trace_status(12024682)
