require 'net/http'

url = URI.parse('http://acm.hdu.edu.cn/search.php?action=listproblem')

response = Net::HTTP.post_form(url,{'content'=>'Robot','searchmode'=>'title'})
puts response.body