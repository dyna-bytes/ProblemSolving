# [Platinum I] The King of the North - 9209 

[문제 링크](https://www.acmicpc.net/problem/9209) 

### 성능 요약

메모리: 84020 KB, 시간: 320 ms

### 분류

최대 유량(flow), 최대 유량 최소 컷 정리(mfmc)

### 문제 설명

<p>Winter is coming (or going? who can be sure these days) and a new king rises in the North. The message travels quickly these days... That is why you, the rising king, have not much time left. You need to rally your bannermen behind you. But one question seems harder to answer than you would have first expected. How large of a kingdom can you claim and how many men should you send for? Your advisors have taken a close look at the potential kingdom and have determined how many of your bannermen would be required to fully defend any part of the map against your foes. As you are a loving and caring king, you want to minimize the number of men that have to serve in your army. To give your war council a fair chance of figuring out the best kingdom to defend, you have to determine the size of the army that you will raise as soon as possible.</p>

<p>Luckily, armies are not that advanced yet. You will only have to defend against armies moving horizontally or vertically (an army cannot pass but your bannermen diagonally). Your kingdom counts as defended, if there is not a single way to reach your castle, starting anywhere outside of the map, without passing to a fully defended area. Squares on the map labeled 0 represent high mountains, or walls, no one would ever be foolish enough to climb. You can assume to be save from invasion without sending any bannermen to defend them. Since you are uncertain about what lurks behind the wall (or in our case the borders of the map), you have to assume the worst and plans as if you would never be able to hold any position outside of the given map.</p>

<p style="text-align: center;"><img alt="" src="https://www.acmicpc.net/upload/images/kingnorth.png" style="height:214px; width:247px"></p>

<p style="text-align: center;"><strong>Figure 2</strong> – Illustration of the sample input — the kingdom can be defended with a minimal army of 37 bannerman, located at the cross-marked positions. The kingdom itself is illustrated using a tiling pattern. Note that you do not have to find out about the kingdom, or the position of you bannermen. These questions are to be figured out by your war council.</p>

### 입력 

 <p>The input is given in the form of the (rectangular) strategic map which your advisors came up with. Every square in map is assigned a number of bannermen which would be required to defend the position against any potential army. The map is formatted as follows: In a first line you are given to integers R and C, 3 ≤ R, C ≤ 300, specifying the dimensions of the map. This line is followed by R lines, each containing C integers 0 ≤ c<sub>i</sub> ≤ 100 000, the number of bannermen necessary to defend each square. Finally, you are given 0 < r < R - 1 and 0 < c < C - 1, the position of your own castle on the map.</p>

### 출력 

 <p>Output an integer on a single line, the smallest possible army you would require to defend any kingdom.</p>

