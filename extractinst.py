#this file takes in input the dot files and gives us the whole CFG related info.
#to run, type extractinst.py filename.


import sys
filename=sys.argv[1]

opcodes=['mov','sub','push','add','test','jz','call','lea','jz','and','movzx','imul',
        'shr','shl','xor','or','pop']

lines=[]

with open(filename) as f:
  lines=f.readlines()


firstlist=[]
secondlist=[]
blockinfo=[]

count=0;
arrow="->"
squarebracket="["

for line in lines:
  count=count+1
  if count>=15 and line.find(arrow)!=-1:
    fineline=line
    splitter=fineline.split('->')
    firstblock=splitter[0].split(' ')[2]
    secondblock=splitter[1].split(' ')[1]
    firstlist.append(firstblock)
    secondlist.append(secondblock)
    #print(firstblock+" -> "+secondblock+"\n")
  elif count>=15 and line.find(squarebracket)!=-1:
    fineline=line
    splitter=fineline.split(' ')
    blocknumber=splitter[2]
    localblockinfo=[]
    localblockinfo.append(blocknumber)
    localblockinfo.append("\n")
    splitline=line
    parts=splitline.split('\l')
    for part in parts:
      for opcode in opcodes:
        if part.find(opcode)!=-1:
          localblockinfo.append(opcode)
          localblockinfo.append("\n")
          break
        else:
          continue
    blockinfo.extend(localblockinfo)
    #print(localblockinfo)
    
fwrite=open("blocks.txt","w")
for x in blockinfo:
  fwrite.write(x)
fwrite.close()

fwrite=open("order.txt","w")

for x, y in zip(firstlist,secondlist):
  fwrite.write(x+" "+y+"\n")
  
fwrite.close()


#print(blockinfo)    
    


