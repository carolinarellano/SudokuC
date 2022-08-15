int SetBoard();
void PrintBoard(int** board);
bool isAvailable(int** board, int* row, int* col);
bool isCorrect(int** board, int row, int col, int input);
bool solution(int** board);
int** copyBoard(int** board);
void player(int** playerBoard, int** tempBoard);