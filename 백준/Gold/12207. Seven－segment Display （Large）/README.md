# [Gold IV] Seven-segment Display (Large) - 12207 

[문제 링크](https://www.acmicpc.net/problem/12207) 

### 성능 요약

메모리: 2168 KB, 시간: 28 ms

### 분류

비트마스킹(bitmask), 브루트포스 알고리즘(bruteforcing)

### 문제 설명

<p>Tom is a boy whose dream is to become a scientist, he invented a lot in his spare time. He came up with a great idea several days ago: to make a stopwatch by himself! So he bought a seven-segment display immediately.</p>

<p>The seven elements of the display are all light-emitting diodes (LEDs) and can be lit in different combinations to represent the arabic numerals like:</p>

<p><img alt="" src="https://onlinejudgeimages.s3.amazonaws.com/problem/12206/images-69.png" style="height:69px; width:429px"></p>

<p>However, just when he finished the programs and tried to test the stopwatch, some of the LEDs turned out to be broken! Some of the segments can never be lit while others worked fine. So the display kept on producing some ambiguous states all the time...</p>

<p>Tom has recorded a continuous sequence of states which were produced by the display and is curious about whether it is possible to understand what this display was doing. He thinks the first step is to determine the state which the display will show <strong>next</strong>, could you help him?</p>

<p>Please note that the display works well despite those broken segments, which means that the display will keep on counting down <strong>cyclically</strong> starting from a certain number (can be any one of 0-9 since we don't know where this record starts from). 'Cyclically' here means that each time when the display reaches 0, it will keep on counting down starting from 9 again.</p>

<p>For convenience, we refer the seven segments of the display by the letters A to G as the picture below:</p>

<p><img alt="" src="https://onlinejudgeimages.s3.amazonaws.com/problem/12206/images-70.png" style="height:93px; width:53px"></p>

<p>For example, if the record of states is like:</p>

<p><img alt="" src="https://onlinejudgeimages.s3.amazonaws.com/problem/12206/images-71.png" style="height:69px; width:213px"></p>

<p>It's not that hard to figure out that ONLY segment B is broken and the sequence of states the display is trying to produce is simply "9 -> 8 -> 7 -> 6 -> 5". Then the next number should be 4, but considering of the brokenness of segment B, the next state should be:</p>

<p><img alt="" src="https://onlinejudgeimages.s3.amazonaws.com/problem/12206/images-72.png" style="height:69px; width:40px"></p>

### 입력 

 <p>The first line of the input gives the number of test cases, <strong>T</strong>. Each test case is a line containing an integer <strong>N</strong> which is the number of states Tom recorded and a list of the <strong>N</strong> states separated by spaces. Each state is encoded into a 7-character string represent the display of segment A-G, from the left to the right. Characters in the string can either be '1' or '0', denoting the corresponding segment is on or off, respectively.</p>

<p>Limits</p>

<ul>
	<li>1 ≤ <strong>T</strong> ≤ 2000.</li>
	<li><span style="line-height:1.6em">1 ≤ </span><strong style="line-height:1.6em">N</strong><span style="line-height:1.6em"> ≤ 100.</span></li>
</ul>

### 출력 

 <p>For each test case, output one line containing "Case #x: y", where x is the test case number (starting from 1). If the input unambiguously determines the next state of the display, y should be that next state (in the same format as the input). Otherwise, y should be "ERROR!".</p>

