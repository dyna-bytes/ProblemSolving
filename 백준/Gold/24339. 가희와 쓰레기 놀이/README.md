# [Gold II] 가희와 쓰레기 놀이 - 24339 

[문제 링크](https://www.acmicpc.net/problem/24339) 

### 성능 요약

메모리: 100612 KB, 시간: 1976 ms

### 분류

값 / 좌표 압축(coordinate_compression), 자료 구조(data_structures), 깊이 우선 탐색(dfs), 그래프 이론(graphs), 그래프 탐색(graph_traversal), 해시를 사용한 집합과 맵(hash_set), 구현(implementation)

### 문제 설명

<p>가희는 친구들과 함께 쓰레기 수집 놀이를 하고 있습니다. 이 놀이를 이해하는 데 필요한 용어를 설명하겠습니다.</p>

<p style="text-align: center;"><img alt="" src=""></p>

<p style="text-align: center;"><strong>[그림 1-1(좌), 그림 1-2 (우)] object 1에서 object 2로 연결하는 연결 관계</strong></p>

<p>먼저 연결 관계란 object에서 object를 연결하는 관계를 의미합니다. 예를 들어, [그림 1-1], [그림 1-2]는 object 1에서 object 2로 연결하는 관계를 나타냅니다. 연결 관계는 약한 연결 관계와, 강한 연결 관계가 있습니다. <strong>이 중, object 1에서 object 2로 연결하는 약한 연결 관계는 [그림 1-1]에, 1에서 2로 연결하는 강한 연결 관계는 [그림 1-2]에 표시되어 있습니다.</strong></p>

<p>가희와 친구들이 수행할 수 있는 연산에 대한 설명은 아래와 같습니다.</p>

<ul>
	<li>M
	<ul>
		<li><strong>root로부터 강한 연결 관계를 통해서만 도달할 수 있는</strong> object만 남기고 나머지 object를 모두 제거합니다.</li>
	</ul>
	</li>
	<li>m
	<ul>
		<li><strong>root로부터 강한 연결, 혹은 약한 연결 관계를 통해서 도달할 수 있는</strong> object만 남기고 나머지 object를 모두 제거합니다.</li>
	</ul>
	</li>
	<li>MADE <code>object_id is_root</code>
	<ul>
		<li>id가 <code>object_id</code>인 object를 추가합니다. <code>is_root</code>의 값이 <code>ROOT</code>이면 해당 object는 root임을 의미합니다.</li>
	</ul>
	</li>
	<li>ADD <code>ref_id object_id_1 </code>-> <code>object_id_2</code>
	<ul>
		<li><code>object_id</code>가 <code>object_id_1</code>인 객체에서 <code>object_id</code>가 <code>object_id_2</code>인 객체를 연결하는, 연결 관계 id가 <code>ref_id</code>인 약한 연결 관계를 추가합니다.</li>
	</ul>
	</li>
	<li>ADD <code>ref_id object_id_1 </code>=> <code>object_id_2</code>
	<ul>
		<li><code>object_id</code>가 <code>object_id_1</code>인 객체에서 <code>object_id</code>가 <code>object_id_2</code>인 객체를 연결하는, 연결 관계 id가 <code>ref_id</code>인 강한 연결 관계를 추가합니다.</li>
	</ul>
	</li>
	<li>REMOVE <code>ref_id</code>
	<ul>
		<li>연결 관계 id가 <code>ref_id</code>인 연결 관계를 제거합니다.</li>
	</ul>
	</li>
</ul>

<p>M과 m 연산이 일어날 때마다, 놀이에 있는 모든 object에 대해, root로부터 도달이 가능한지를 판단하게 됩니다. root에서 object x가 도달 가능하다는 것은, 아래 조건 중 하나 이상을 만족합니다.</p>

<ul>
	<li>object x는 root입니다.</li>
	<li>root에서 조건을 만족하는 연결 관계를 거쳐서 object x에 도달할 수 있습니다.</li>
</ul>

<p style="text-align: center;"><img alt="" src=""></p>

<p style="text-align: center;"><strong>[그림 2-1 (좌), 그림 2-2 (우)]</strong></p>

<p>[그림 2-1], [그림 2-2]에서 root는 노란색으로 칠해져 있습니다. [그림 2-1]은 1에서 2로 연결하는 강한 연결 관계와 2에서 3으로 연결하는 강한 연결 관계가 있음을 나타냅니다. root로부터 도달 가능한 object는 1, 2, 3입니다. [그림 2-2]는 1에서 2로 연결하는 강한 연결 관계와 2에서 3으로 연결하는 약한 연결 관계가 있음을 나타냅니다. 강한 연결 관계나 약한 연결 관계를 통해서 root로부터 도달 가능한 object는 1, 2, 3입니다. <strong>하지만, 강한 연결 관계를 통해서만 도달할 수 있는 object는 1과 2뿐입니다.</strong> root인 1에서 root가 아닌 3으로 가기 위해서는 2에서 3으로 연결하는 약한 연결 관계를 반드시 통해야 하기 때문입니다.</p>

<p>이 놀이의 규칙은 다음과 같습니다.</p>

<ul>
	<li>게임이 시작되기 전에는 생성된 object 중에 root 역할을 하는 object가 있을 수도 없을 수도 있습니다.</li>
	<li>게임이 시작되기 전에는 object와 object를 연결하는 <strong>어떠한 연결 관계도 존재하지 않습니다.</strong></li>
	<li>가희와 친구들은 게임이 진행되는 동안 여러 연산을 할 수 있습니다.</li>
</ul>

<p>object가 제거될 때, 제거된 object로부터 다른 object를 연결하는 연결 관계와 다른 object에서 제거된 object, 그리고 제거된 object로부터 제거된 object로 연결되는 <strong>연결 관계들이 모두 제거</strong>됩니다. 게임을 시작하기 전 생성된 object들과 게임 중에 가희와 친구들이 한 연산들이 시간 순서대로 주어집니다. 가희와 친구들이 연산을 수행할 때마다, 연산을 수행하고 남은 object의 수를 출력해 주세요.</p>

### 입력 

 <p>첫 번째 줄에 게임이 시작되기 전 생성된 object의 개수 <em>O</em>와 게임에서 가희와 친구들이 수행한 연산의 개수 <em>E</em>가 공백으로 구분되어 주어집니다.</p>

<p>다음 O개의 줄에는 <code>object_id</code>와 <code>is_root</code>가 공백으로 구분되어 주어집니다.</p>

<p>이때 <code>is_root</code>는 해당 object가 root라면 ROOT, 아니라면 -로 주어지며, <strong>주어지는 <code>object_id</code>는 모두 다릅니다.</strong></p>

<p>다음 <em>E</em>개의 줄에는 문제에서 설명한 연산 중 하나가 <strong>발생한 시간 순서대로</strong> 주어집니다.</p>

### 출력 

 <p><strong>M과 m 연산이 주어질 때마다</strong> 해당 연산을 수행하고 난 후에 남아 있는 object의 개수를 한 줄에 하나씩 출력해 주세요.</p>

