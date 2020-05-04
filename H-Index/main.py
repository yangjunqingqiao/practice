class Priority_Queue():
    def __init__(self):
        self.values = [0]
    
    def insert(self, value):
        self.values.append(value)
        self.percolate_up()
        
    def percolate_up(self):
        i = len(self.values) - 1
        while i//2 > 0:
            if self.values[i] < self.values[i//2]:
                self.values[i], self.values[i//2] = self.values[i//2], self.values[i]
                i = i//2
            else:
                break
        
    def remove_min(self):
        self.values[1] = self.values.pop()
        self.percolate_down(1) 
        
    def min_child(self, i):
        if i*2 + 1 >= len(self.values):
            if i*2 < len(self.values):
                return i*2
            else:
                return i

        if self.values[i*2] < self.values[i*2 + 1]:
            return i*2
        return i*2+1
        
    def get_min(self):
        if len(self.values) > 1:
            return self.values[1]
        return 0
        
    def percolate_down(self, i):
        while i*2 < len(self.values):
            m = self.min_child(i)
            if self.values[i] > self.values[m]:
                self.values[i], self.values[m] = self.values[m], self.values[i]
                i = m
            else:
                break
    
    def purge(self, val):
        while self.get_min() <= val:
            self.remove_min()
                
    def __len__(self):
        return len(self.values) - 1


if __name__ == '__main__':
    num_cases = int(input())
    for i in range(num_cases):
        num_papers = int(input())
        citations = [int(x) for x in input().split(' ')]
        out = 'Case #' + str(i+1) + ':'
        
        seen = Priority_Queue()
        prev_val = 0
        
        for j in range(num_papers):
            if citations[j] > prev_val:
                seen.insert(citations[j])
                if len(seen) > prev_val:
                    seen.purge(prev_val)
                    if len(seen) > prev_val:
                        prev_val = len(seen)

            out += ' ' + str(prev_val)
        
        print(out)