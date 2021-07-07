execfile('20141555.conf')

from boto.dynamodb2.table import Table
from boto.s3.connection import S3Connection

#S3 로부터 bucket get
s3 = S3Connection()
bucket = s3.get_bucket('20141555tokyo')

#project6 table
dynamoTable = Table('project6')
#bucket의 list들 얻음
temp = bucket.list()

for i in temp:
	if 'project5output' in i.key and 'part-' in i.key:
        #get content as string in a file
		content = i.get_contents_as_string()
        #split line by enter
		for line in content.split('\n'):
			if line == "":
				continue
            #split line by tab
			words,counts = line.split('\t')
            #put item in the dynamoTable
			dynamoTable.put_item(data={'words':words, 'counts':counts})

