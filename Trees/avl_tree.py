class AvlTree:
    def __init__(self, val):
        self.value = val
        self.right = None
        self.left = None
        self.balance = 0
    
    def __len__(self):
        if self.value == None:
            return 0
        else:
            return 1 + max(len(self.right), len(self.left))

    def inorder(self):
        values = []
        values += self.left.inorder()
        if self.value is not None:
            values += [self.value]
        values += self.right.inorder()
        return values

    def set_right (self, node: AvlTree):
        self.right = node
    
    def set_left(self, node: AvlTree):
        self.left = node

    def insert(self, val):
        if self.value == None:
            self.value = val
        elif val <= self.value:
            if self.left == None:
                self.left = AvlTree(val)
            else:
                self.left.insert(val)
        else:
            if self.right == None:
                self.right = AvlTree(val)
            else:
                self.right.insert(val)

    def display(self):
        line_down = []
        if self.value is not None:
            line_down.append(self.value)
            line_down.append(self.left)
            line_down.append(self.right)