# [Gold III] 가희와 파일 탐색기 2 - 25240 

[문제 링크](https://www.acmicpc.net/problem/25240) 

### 성능 요약

메모리: 195848 KB, 시간: 1996 ms

### 분류

자료 구조(data_structures), 해시를 사용한 집합과 맵(hash_set), 구현(implementation), 파싱(parsing), 문자열(string)

### 문제 설명

<p>가희는 <code>jo_test</code><em> </em>폴더에 들어와 있습니다. <code>jo_test</code><em> </em>폴더에는 일반 파일이 <em>N</em>개 있습니다.</p>

<p>각각의 파일에는 권한이 있습니다. 권한이란 어떤 유저가 특정한 일을 수행할 수 있는지를 나타내며, 3개의 숫자로 구성됩니다.</p>

<table align="center" border="1" cellpadding="1" cellspacing="1" class="table table-bordered" style="width: 500px;">
	<tbody>
		<tr>
			<td style="text-align: center;">숫자</td>
			<td style="text-align: center;">권한</td>
		</tr>
		<tr>
			<td style="text-align: center;">0</td>
			<td style="text-align: center;">아무것도 할 수 없음</td>
		</tr>
		<tr>
			<td style="text-align: center;">1</td>
			<td style="text-align: center;">실행 권한이 있음</td>
		</tr>
		<tr>
			<td style="text-align: center;">2</td>
			<td style="text-align: center;">수정 권한이 있음</td>
		</tr>
		<tr>
			<td style="text-align: center;">3</td>
			<td style="text-align: center;">실행 권한과 수정 권한이 있음</td>
		</tr>
		<tr>
			<td style="text-align: center;">4</td>
			<td style="text-align: center;">읽기 권한이 있음</td>
		</tr>
		<tr>
			<td style="text-align: center;">5</td>
			<td style="text-align: center;">읽기와 실행 권한이 있음</td>
		</tr>
		<tr>
			<td style="text-align: center;">6</td>
			<td style="text-align: center;">읽기와 수정 권한이 있음</td>
		</tr>
		<tr>
			<td style="text-align: center;">7</td>
			<td style="text-align: center;">읽기와 실행, 수정 권한이 있음 </td>
		</tr>
	</tbody>
</table>

<p style="text-align: center;"><strong>[표 1] 숫자와 해당되는 권한</strong></p>

<p>3개의 숫자 중 1번째 숫자는, 파일을 소유하고 있는 유저가 어떤 권한을 가지고 있는지를 나타냅니다. 2번째 숫자는, 파일을 소유하고 있는 그룹이 어떤 권한을 가지고 있는지를 나타냅니다. 3번째 숫자는, <strong>파일을 소유하고 있는 그룹에 속하지 않고, 파일을 소유하고 있는 유저가 아닌 경우</strong> 어떤 권한을 가지고 있는지를 나타냅니다.</p>

<p>예를 들어 파일 <code>train_mugunghwa</code>의 권한이 750이고 이 파일을 소유하고 있는 유저가 <code>cho</code>, 소유하고 있는 그룹이 <code>gahui</code>라고 하겠습니다. 그리고, 그룹 <code>gahui</code>에 속한 유저가 <code>cho1</code>, <code>cho2</code>라고 하겠습니다. 이때, 유저 <code>cho</code>는 <code>train_mugunghwa</code>에 대해서 읽기, 실행, 수정 권한이 있습니다. 유저 <code>cho2</code>는 파일 <code>train_mugunghwa</code>를 가지고 있는 그룹에 속하므로 <code>train_mugunghwa</code>에 대해서 읽기와 실행 권한이 있습니다. 마지막으로 유저 <code>gahui</code>는 유저 <code>cho</code>가 아니고, 해당 파일을 소유하고 있는 그룹인 <code>gahui</code>에도 속하지 않으므로 이 파일에 대해서 아무것도 할 수 없습니다.</p>

<p>유저와 그룹, 폴더 <code>jo_test</code>안에 있는 파일에 대한 정보가 주어집니다. 유저가 <code>jo_test</code>안에 있는 파일에 대해서 읽기, 수정, 실행을 시키려고 할 때 성공하는지 실패하는지에 대한 정보를 출력해 주세요.</p>

### 입력 

 <p>첫 줄에 유저에 대한 정보 개수 <em>U</em>와 <code>jo_test</code>폴더 안에 있는 파일에 대한 정보 개수 <em>F</em>가 공백으로 구분되어 주어집니다.</p>

<p>다음 <em>U</em>개의 줄에는 유저에 대한 정보가 주어집니다. 유저에 대한 정보는 아래 형식들 중 하나로 주어집니다.</p>

<ul>
	<li><code>USER_NAME</code>

	<ul>
		<li>유저 <code>USER_NAME</code>이 있다. 유저 <code>USER_NAME</code>이 속한 그룹에 대한 정보는 없다.</li>
	</ul>
	</li>
	<li><code>USER_NAME USER_GROUPS</code>
	<ul>
		<li>유저 <code>USER_NAME</code>이 속한 그룹에 대한 정보는 <code>USER_GROUPS</code>에 있다.</li>
	</ul>
	</li>
</ul>

<p>유저가 속한 그룹이 여러 개라면 ',' (콤마)로 구분되어 주어집니다. 또한 <code>USER_NAME</code>은 자동으로 그룹 이름이 <code>USER_NAME</code>인 그룹에 속합니다. <strong>유저가 속한 그룹들에 대한 정보에 <code>USER_NAME</code>이 주어지지 않더라도 그룹 이름이 <code>USER_NAME</code>인 그룹에 속함에 주의하세요.</strong></p>

<p>다음 <em>F</em>개의 줄에는 파일에 대한 정보가 아래 형식으로 주어집니다.</p>

<ul>
	<li><code>FILE_NAME</code> <code>FILE_PERMISSION OWNER OWNED_GROUP</code></li>
</ul>

<p>이 정보는 파일 이름이 <code>FILE_NAME</code>인 파일 권한이 <code>FILE_PERMISSION</code>이고, 소유자가 <code>OWNER</code>, 소유 그룹이 <code>OWNED_GROUP</code>임을 의미합니다. 이때, 파일 <code>FILE_NAME</code>에 대해 각 유저들이 가지는 권한 이름은 아래와 같습니다.</p>

<table align="center" border="1" cellpadding="1" cellspacing="1" class="table table-bordered" style="width: 500px;">
	<tbody>
		<tr>
			<td style="text-align: center;">유저</td>
			<td style="text-align: center;">권한</td>
		</tr>
		<tr>
			<td style="text-align: center;"><code>OWNER</code></td>
			<td style="text-align: center;"><code>OWNER</code></td>
		</tr>
		<tr>
			<td style="text-align: center;"><code>OWNER</code>는 아니지만, <code>OWNER_GROUP</code>에 속한 유저</td>
			<td style="text-align: center;"><code>GROUP</code></td>
		</tr>
		<tr>
			<td style="text-align: center;"><code>OWNER</code>도 아니고, <code>OWNER_GROUP</code>에 속하지도 않는 유저</td>
			<td style="text-align: center;"><code>OTHER</code></td>
		</tr>
	</tbody>
</table>

<p style="text-align: center;"><strong>[표 2] 유저가 이름이 <code>FILE_NAME</code>인 파일에 대해 가지는 권한</strong></p>

<p>그 다음 줄에 질문의 개수 <em>Q</em>가 주어집니다.</p>

<p>다음 <em>Q</em>개의 줄에는 <code>USER_NAME</code>과 <code>FILE_NAME</code>과 <code>OPERATION</code>이 공백으로 구분되어 주어집니다. <code>OPERATION</code>은 문자 'R', 'W', 'X' 중 하나로 주어지며, 각각의 의미는 읽기, 수정, 실행을 의미합니다. 또한 입력의 의미는 유저 <code>USER_NAME</code>이 파일 <code>FILE_NAME</code>에 연산 <code>OPERATION</code>을 수행하려고 하는지 나타냅니다.</p>

### 출력 

 <p><em>Q</em>개의 질문에 대해, 연산이 성공하면 1을 실패하면 0을 출력해 주세요. <strong>각 질문에 대한 답은 한 줄에 하나씩 출력해 주세요.</strong></p>

