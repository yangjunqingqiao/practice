#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Board {
    int dim;
    vector<char> board;

    private:
        int translate_coords(int x, int y) {
            return x*dim + y;
        }
        
        char flip(char c) {
            if(c == '#') {
                return '.';
            }
            return '#';
        }
        
        // x, y denote the coordinates of the pivot node
        vector<char> flip_forward(int x, int y, vector<char> b) {
            int temp_x = x;
            int temp_y = y;
            vector<char> new_b = b;
            while(temp_x >= 0 and temp_y < dim) {
                new_b[this->translate_coords(temp_x, temp_y)] = 
                    flip(new_b[this->translate_coords(temp_x, temp_y)]);
                temp_x--;
                temp_y++;
            }
            temp_x = x + 1;
            temp_y = y - 1;
            while(temp_x < dim and temp_y >= 0) {
                new_b[this->translate_coords(temp_x, temp_y)] = 
                    flip(new_b[this->translate_coords(temp_x, temp_y)]);
                temp_x++;
                temp_y--;
            }
            return new_b;
        }
        
        vector<char> flip_backward(int x, int y, vector<char> b) {
            int temp_x = x;
            int temp_y = y;
            vector<char> new_b = b;
            while(temp_x >= 0 and temp_y >= 0) {
                new_b[this->translate_coords(temp_x, temp_y)] = 
                    flip(new_b[this->translate_coords(temp_x, temp_y)]);
                temp_x--;
                temp_y--;
            }
            temp_x = x + 1;
            temp_y = y + 1;
            while(temp_x < dim and temp_y < dim) {
                new_b[this->translate_coords(temp_x, temp_y)] = 
                    flip(new_b[this->translate_coords(temp_x, temp_y)]);
                temp_x++;
                temp_y++;
            }
            return new_b;
        }
        
        bool is_solved(vector<char> b) {
            vector<char>::iterator it = find(b.begin(), b.end(), '.');
            if (it != b.end()) {
            	return false;
            }
            else {
            	return true;
            }
        }
        
        int solve(vector<char> b, int starting) {
            
            // this->print(b);
            
            int x = 0, y = 0;
            while(x < dim) {
                if(b[this->translate_coords(x, y)] == '.'){
                    b = this->flip_forward(x, y, b);
                    starting++;
                }
                x++;
                y++;
            }
            
            // this->print(b);
            
            x = dim-1;
            y = 0;
            while(x >= 0) {
                if(b[this->translate_coords(x, y)] == '.'){
                    b = this->flip_backward(x, y, b);
                    starting++;
                }
                x--;
                y++;
            }
            
            // this->print(b);

            x = dim-1;
            y = 1;
            while(x >= 0 and y < dim) {
                if(b[this->translate_coords(x, y)] == '.'){
                    b = this->flip_backward(x, y, b);
                    starting++;
                }
                x--;
                y++;
            }
            
            // this->print(b);

            x = 1;
            y = 0;
            while(x < dim) {
                if(b[this->translate_coords(x, y)] == '.'){
                    b = this->flip_forward(x, y, b);
                    starting++;
                }
                x++;
                y++;
            }
            
            // this->print(b);
            
            if (this->is_solved(b)) {
                return starting;
            }
            else {
                return 4*dim - 2;
            }
        }
        
        vector<char>* permute_secondary_diags(vector<char> b, vector<char>* permuted_b) {
            permuted_b[0] = b;
            permuted_b[1] = this->flip_forward(dim-1, 1, b);
            permuted_b[2] = this->flip_backward(1, 0, b);
            permuted_b[3] = this->flip_forward(dim-1, 1, \
                    this->flip_backward(1, 0, b));
            return permuted_b;
        }
        
    public:
        Board(int d, string board_string) {
            dim = d;
            copy(board_string.begin(), board_string.end(), back_inserter(board));
        }
        
        void print(vector<char> b) {
            for(int i=0; i<dim; i++) {
                for(int j=0; j<dim; j++) {
                    cout << b[i*dim + j];
                }
            }
            cout << "\n";
        }

        int compute_min_moves() {
            int min_moves=4*dim - 2;
            vector <char> board1 = board;
            vector <char> board2 = this->flip_forward(dim-1, 0, board);
            vector <char> board3 = this->flip_backward(0, 0, board);
            vector <char> board4 = \
                this->flip_forward(dim-1, 0, \
                    this->flip_backward(0, 0, board));
            
            if (dim>2) {
                vector<int> moves;
                int starting_moves[4] = {0, 1, 1, 2};
                vector<char> b1_ptr[4];
                vector<char> b2_ptr[4];
                vector<char> b3_ptr[4];
                vector<char> b4_ptr[4];
                vector<char>* board1s = this->permute_secondary_diags(board1, b1_ptr);
                vector<char>* board2s = this->permute_secondary_diags(board2, b2_ptr);
                vector<char>* board3s = this->permute_secondary_diags(board3, b3_ptr);
                vector<char>* board4s = this->permute_secondary_diags(board4, b4_ptr);
                for(int i=0; i<4; i++) {
                    // this->print(board1s[i]);
                    moves.push_back(this->solve(*(board1s + i), 0 + starting_moves[i]));
                    moves.push_back(this->solve(*(board2s + i), 1 + starting_moves[i]));
                    moves.push_back(this->solve(*(board3s + i), 1 + starting_moves[i]));
                    moves.push_back(this->solve(*(board4s + i), 2 + starting_moves[i]));
                }
                return *min_element(moves.begin(), moves.end());
            }
            else {
                int moves[4];
                moves[0] = this->solve(board1, 0);
                moves[1] = this->solve(board2, 1);
                moves[2] = this->solve(board3, 1);
                moves[3] = this->solve(board4, 2);
                pair<int*, int*>minmax = minmax_element(begin(moves), end(moves));
                return *minmax.first;
            }
        }
};

int main() {
    int test_cases;
    cin >> test_cases;
    for(int i=0; i < test_cases; i++) {
        int min_moves = 0;
        int d;
        cin >> d;
        string rows="";
        for(int i=0; i<d; i++) {
            string row;
            cin >> row;
            rows.append(row);
        }
        Board* b = new Board(d, rows);
        min_moves = b->compute_min_moves();
        cout << "Case #" << i+1 << ": " << min_moves << "\n";
    }
}