require 'net/http'

def my_post(uri,data)
	cookie = "PHPSESSID=dmgqajp0bp0o4f3r3eu183l8v2"
	req = Net::HTTP::Post.new(uri.path)
	req.set_form_data(data)
	req['Cookie']=cookie

	res=Net::HTTP.start(uri.hostname, uri.port) do |http|
		http.request(req)
	end
	res
end
=begin
def search(content,searchmode='title')
	uri = URI('http://acm.hdu.edu.cn/search.php?action=listproblem')
	data = {
		#'action'=>'listproblem',
		'content'=>content,
		'searchmode'=>searchmode
	}
	my_post(uri,data)
#	Net::HTTP.post(uri,data)
end
=end
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
		'check'=>0,
		'problemid'=>id,
		'language'=>language,
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

#puts search("shit").body
puts submit(4576,"tp.cpp")
#puts trace_status(12024682)
