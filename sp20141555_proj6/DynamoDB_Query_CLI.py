execfile('20141555.conf')

from boto.dynamodb2.table import Table

myTable = Table('project6')

#until input is "" continue
while True:
	str1=raw_input("Input string:")
	if str1 == "":
		break
    #dynamoDB table 에서 str1 과 같은 words find
	temp = myTable.get_item(words = str1)
	if temp:
        # exist, print counts
		print "words: " + temp['words']
		print "counts: " + str(temp['counts'])
	else:
        #not exist, print error
		print str1 + " is not in dynamoDB table"
