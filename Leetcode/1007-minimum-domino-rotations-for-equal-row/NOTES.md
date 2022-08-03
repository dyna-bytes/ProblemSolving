f(n, target)
if(top[n] == target)
f(n+1, target)
elif(bottom[n] == target)
do flip
1 + f(n+1, target)
else
return -1;
f(0, top[0]), f(0, bottom[0]) 을 각각 한 번씩 호출