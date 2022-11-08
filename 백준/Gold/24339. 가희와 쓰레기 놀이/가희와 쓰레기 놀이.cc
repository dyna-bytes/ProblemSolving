#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <list>
using namespace std;
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl;
#define debugVec(v) do{\
	cout << "[debug] " << #v << endl;\
	for (auto e: v) cout << e << " | ";\
	cout << endl;\
}while(0);

struct Object {
	int object_id;
	bool is_root;
	unordered_set<int> strongs;
	unordered_set<int> weeks;
};

struct Reference {
	int ref_id;
	Object* from;
	Object* to;
};

unordered_map<int, Object*> objects;
unordered_map<int, Reference*> strong_refs;
unordered_map<int, Reference*> week_refs;
unordered_map<Object*, int> visited;

void ADD_STRONG(int ref_id, int object_id_1, int object_id_2) {
	Reference* ref = new Reference();

	ref->ref_id = ref_id;
	ref->from = objects[object_id_1];
	ref->to = objects[object_id_2];

	objects[object_id_1]->strongs.insert(ref_id);
	strong_refs[ref_id] = ref;
}

void ADD_WEEK(int ref_id, int object_id_1, int object_id_2) {
	Reference* ref = new Reference();

	ref->ref_id = ref_id;
	ref->from = objects[object_id_1];
	ref->to = objects[object_id_2];

	objects[object_id_1]->weeks.insert(ref_id);
	week_refs[ref_id] = ref;
}

void MADE(int object_id, bool is_root) {
	Object* obj = new Object();

	obj->object_id = object_id;
	obj->is_root = is_root;

	objects[object_id] = obj;
}

void REMOVE(int ref_id) {
	if (strong_refs.find(ref_id) != strong_refs.end()) {
		Reference* ref = strong_refs[ref_id];
		(ref->from)->strongs.erase(ref_id);
		strong_refs.erase(ref_id);
	}
	else if (week_refs.find(ref_id) != week_refs.end()) {
		Reference* ref = week_refs[ref_id];
		(ref->from)->weeks.erase(ref_id);
		week_refs.erase(ref_id);
	}
}

void dfs(Object* curr, bool erase_only_strong) {
	visited[curr] = true;

	for (int ref_id : curr->strongs) {
		if (strong_refs.find(ref_id) == strong_refs.end()) continue;

		Object* next = strong_refs[ref_id]->to;
		if (visited[next]) continue;

		dfs(next, erase_only_strong);
	}

	if (erase_only_strong) return;

	for (int ref_id : curr->weeks) {
		if (week_refs.find(ref_id) == week_refs.end()) continue;

		Object* next = week_refs[ref_id]->to;
		if (visited[next]) continue;

		dfs(next, erase_only_strong);
	}
}

// 강한 연결 관계로 도달 가능한 노드만 남기고, 모든 노드 삭제. 남은 노드의 수 반환
int M() {
	visited.clear();
	for (auto p : objects) {
		Object* obj = p.second;
		if (obj->is_root && !visited[obj])
			dfs(obj, true);
	}

	list<int> del_obj;
	for (auto p : objects) {
		int obj_id = p.first;
		Object* obj = p.second;
		if (!visited[obj]) 
			del_obj.push_back(obj_id);
	}

	for (int obj_id : del_obj) {
		Object* obj = objects[obj_id];
		for (int ref_id : obj->strongs) 
			strong_refs.erase(ref_id);
		
		for (int ref_id : obj->weeks) 
			week_refs.erase(ref_id);
		
		objects.erase(obj_id);
	}

	return objects.size();
}

// 강/약 연결 관계로 도달 가능한 노드만 남기고 모든 노드 삭제. 남은 노드의 수 반환
int m() {
	visited.clear();
	for (auto p : objects) {
		Object* obj = p.second;
		if (obj->is_root && !visited[obj])
			dfs(obj, false);
	}

	list<int> del_obj;
	for (auto p : objects) {
		int obj_id = p.first;
		Object* obj = p.second;
		if (!visited[obj])
			del_obj.push_back(obj_id);
	}

	for (int obj_id : del_obj) {
		Object* obj = objects[obj_id];
		for (int ref_id : obj->strongs) {
			strong_refs.erase(ref_id);
		}
		for (int ref_id : obj->weeks) {
			week_refs.erase(ref_id);
		}
		objects.erase(obj_id);
	}

	return objects.size();
}

void debugNodes() {
	for (auto p : objects) {
		int obj_id = p.first;
		Object* obj = p.second;

		debug(obj_id);
		for (int strong_ref_id : obj->strongs) {
			debug(strong_ref_id);
			Object* to = strong_refs[strong_ref_id]->to;
			debug(to->object_id);
		}

		for (int week_ref_id : obj->weeks) {
			debug(week_ref_id);
			Object* to = week_refs[week_ref_id]->to;
			debug(to->object_id);
		}
	}
}

int main() {
	int O, E;
	cin >> O >> E;
	for (int i = 0; i < O; i++) {
		int object_id;
		string is_root;
		cin >> object_id >> is_root;
		if (is_root == "ROOT") MADE(object_id, true);
		else MADE(object_id, false);
	}

	for (int i = 0; i < E; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "MADE") {
			int object_id;
			string is_root;
			cin >> object_id >> is_root;
			if (is_root == "ROOT") MADE(object_id, true);
			else MADE(object_id, false);
		}
		if (cmd == "ADD") {
			int ref_id;
			int object_id_1, object_id_2;
			string is_strong;
			cin >> ref_id >> object_id_1 >> is_strong >> object_id_2;

			if (is_strong == "=>") ADD_STRONG(ref_id, object_id_1, object_id_2);
			else ADD_WEEK(ref_id, object_id_1, object_id_2);	
		}
		if (cmd == "M") {
			cout << M() << endl;
		}
		if (cmd == "m") {
			cout << m() << endl;
		}
		if (cmd == "REMOVE") {
			int ref_id; 
			cin >> ref_id;
			REMOVE(ref_id);
		}
	}
	//debugNodes();
	return 0;
}