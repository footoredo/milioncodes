require 'net/http'

def my_post(uri,data)
	cookie = "PHPSESSID=dmgqajp0bp0o4f3r3eu183l8v2"
	cookie = "exesubmitlang=0; PHPSESSID=nr6bcri83c46l7353b7o2omem7"
	req = Net::HTTP::Post.new(uri.path)
	req.set_form_data(data)
	req['Cookie']=cookie

	res=Net::HTTP.start(uri.hostname, uri.port) do |http|
		http.request(req)
	end
	res
end

def my_get(uri)
	http=Net::HTTP.new('acm.hdu.edu.cn')
	cookie = "PHPSESSID=nr6bcri83c46l7353b7o2omem7"
	#uri = URI('http://poj.org/showsource?solution_id='+id.to_s)
	#data = 'solution_id='+id.to_s
	headers = { 'Cookie'=>cookie }
	res=http.get(uri,headers).body
end

def search(content,searchmode='title')
	uri = URI('http://acm.hdu.edu.cn/search.php?field=problem&key='+
		content+'&searchmode='+searchmode)
=begin
	data = {
		#'action'=>'listproblem',
		'field'=>'problem',
		'key'=>content,
		'searchmode'=>searchmode
		#searchmode=>1
	}
=end
	my_get(uri)
#	Net::HTTP.post(uri,data)
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

	uri = URI('http://acm.hdu.edu.cn/submit.php')
	data = {
		'action'=>'submit',
		'check'=>'0',
		'problemid'=>id.to_s,
		'language'=>language.to_s,
		'usercode'=>code
	}
	my_post(uri,data)
	#get_run_id(id,language)
end

def get_status(name,res)
	tr=/#{name}.+<\/td>/.match(res)
	tr=/>[a-zA-Z0-9 \/]{4,}</.match(tr.to_s)
	/[a-zA-Z0-9 \/]{4,}/.match(tr.to_s)
end

def trace_status(id)
	http=Net::HTTP.new('poj.org')
	cookie = "exesubmitlang=0; PHPSESSID=dmgqajp0bp0o4f3r3eu183l8v2"
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

def tttt
	uri = URI('http://acm.hdu.edu.cn/submit.php?pid=4576')
	my_get(uri)
end

#puts search("shit")
puts submit(4576,"tp.cpp")
#puts tttt
#puts trace_status(12024682)
