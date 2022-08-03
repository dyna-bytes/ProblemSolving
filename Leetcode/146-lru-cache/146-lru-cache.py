class ListNode:
    def __init__(self, key: int, val: int):
        self.key = key
        self.val = val
        self.prev: ListNode = None
        self.next: ListNode = None

class LRUCache:
    def __init__(self, capacity: int):
        self.cap: int = capacity
        self.hashmap: Dict[int, ListNode] = {}
        self.head = ListNode(-1, -1)
        self.tail = ListNode(-1, -1)
        self.head.next = self.tail
        self.tail.prev = self.head

    def insertBack(self, node: ListNode) -> None:
        tail_prev: ListNode = self.tail.prev

        tail_prev.next = node
        node.prev = tail_prev

        self.tail.prev = node
        node.next = self.tail

    def deleteNode(self, node: ListNode) -> None:
        prev_node: ListNode = node.prev
        next_node: ListNode = node.next

        prev_node.next = next_node
        next_node.prev = prev_node

    def get(self, key: int) -> int:
        node: ListNode = self.hashmap.get(key)
        if node is None: return -1
        
        self.deleteNode(node)
        self.insertBack(node)
        return node.val
    
    def put(self, key: int, value: int) -> None:
        if self.get(key) != -1:
            self.hashmap.get(key).val = value
            return
        
        node = ListNode(key, value)
        self.insertBack(node)
        self.hashmap[key] = node

        if len(self.hashmap) > self.cap:
            lru_node: ListNode = self.head.next
            self.hashmap.pop(lru_node.key)
            self.deleteNode(lru_node)



# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)