#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Priority_Queue {
    vector<T> citations;
    private:
        T min_child(int i) {
            if(i*2 + 1 >= citations.size()) {
                if(i*2 < citations.size()) {
                    return i*2;
                }
                else {
                    return i;
                }
            }
            if(citations[i*2] < citations[i*2 + 1]) {
                return i*2;
            }
            return i*2 + 1;
        }
            
        void percolate_down(int i) {
            while(i * 2 < citations.size()) {
                int mc = this->min_child(i);
                if(citations[i] > citations[mc]) {
                    T temp = citations[i];
                    citations[i] = citations[mc];
                    citations[mc] = temp;
                    i = mc;
                }
                else{
                    break;
                }
            }
        }
        
        void percolate_up(int i) {
            while((i/2) > 0) { 
                if(citations[i] < citations[i/2]) {
                    T temp = citations[i];
                    citations[i] = citations[i/2];
                    citations[i/2] = temp;
                    i = i/2;
                }
                else{
                    break;
                }
            }
        }
    public:
        Priority_Queue(){
            citations.push_back(0);
        };
        
        T min_val() {
            if(citations.size() > 1) {
                return citations[1];
            }
            return 0;
        }
        T remove_min() {
            int root = 0;
            if(citations.size() > 1){
                root = citations[1];
                citations[1] = citations.back();
                citations.pop_back();
                this->percolate_down(1);
            }
            return root;
        }
        void insert(T item) {
            citations.push_back(item);
            this->percolate_up(citations.size() - 1);
        }
        void purge(T item) {
            while(this->min_val() <= item) {
                this->remove_min();
            }
        }
        int size() {
            return citations.size() - 1;
        }
        void print() { 
            cout << "Printing:";
            for (int i = 0; i < citations.size(); i++) {
                cout << " " << citations[i];
            }
            cout << "\n";
        }
};

int main() {
    int test_cases;
    cin >> test_cases;
    
    for(int i; i < test_cases; i++){
        int num_papers;
        cin >> num_papers;
        
        cout << "Case #" << i+1 << ":";

        int prev_val = 0;
        Priority_Queue<int>* seen = new Priority_Queue<int>();
        // seen->print();
        for(int j = 1; j <= num_papers; j++){
            int citation;
            cin >> citation;
            
            // cout << "Citation: " << citation << "\n";
            
            if(citation > prev_val) {
                seen->insert(citation);
                if(seen->size() > prev_val) {
                    seen->purge(prev_val);
                    if(seen->size() > prev_val) {
                        prev_val = seen->size();
                    }
                }
            }
            cout << " " << prev_val;
            // cout << "Prev val: " << prev_val << "\n";
            // seen->print();
        }
        cout << "\n";
        delete seen;
    }
}