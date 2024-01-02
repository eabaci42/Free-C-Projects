#include <unistd.h>
#include <stdlib.h>

// Outputs a single character to the console
void ft_putchar(char c) {
    write(1, &c, 1);
}

// Outputs a string to the console
void ft_putstr(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        ft_putchar(str[i]);
        i++;
    }
}

// Gets input from the user for the board position
int get_user_input(int player) {
    char buffer[3]; // Buffer for input: 2 for the number, 1 for null terminator
    int read_bytes;

    // Prompting the current player to choose a square
    ft_putstr("Player ");
    ft_putchar(player + '0'); 
    ft_putstr(" (");
    ft_putchar(player == 1 ? 'X' : 'O');
    ft_putstr("), choose a square (1-9): ");

    read_bytes = read(0, buffer, 2);

    if (read_bytes > 0) {
        buffer[read_bytes] = '\0'; // Correctly null terminate the string
        int position = atoi(buffer);
        if (position >= 1 && position <= 9) {
            return position;
        }
    }

    ft_putstr("Invalid input. Please try again.\n");
    return 0;
}

// Displays the current state of the game board
void display_board(char *board) {
    ft_putstr("\n");
    for (int i = 0; i < 9; i++) {
        ft_putchar(board[i]);
        if ((i + 1) % 3 == 0 && i != 8) {
            ft_putstr("\n-+-+-\n");
        } else if (i != 8) {
            ft_putstr("|");
        }
    }
    ft_putstr("\n\n");
}

// Checks for a winning combination on the board
char check_for_winner(char *board) {
    // Checking rows, columns, and diagonals for a winning combination
    // Rows
    for (int row = 0; row < 9; row += 3) {
        if (board[row] == board[row + 1] && board[row + 1] == board[row + 2]) {
            return board[row];
        }
    }

    // Columns
    for (int col = 0; col < 3; col++) {
        if (board[col] == board[col + 3] && board[col + 3] == board[col + 6]) {
            return board[col];
        }
    }

    // Diagonals
    if (board[0] == board[4] && board[4] == board[8]) {
        return board[0];
    }
    if (board[2] == board[4] && board[4] == board[6]) {
        return board[2];
    }

    // No winner yet
    return '\0';
}

// Main function: entry point of the program
int main() {
    char board[] = {'1','2','3','4','5','6','7','8','9'};
    int current_player = 1;
    int total_moves = 0;
    char winner = '\0';

    ft_putstr("Welcome to Two-Player Tic-Tac-Toe!\n");
    ft_putstr("Player 1 is X and Player 2 is O.\n\n");

    while (winner == '\0' && total_moves < 9) {
        display_board(board);

        int selected_square = 0;
        while (selected_square < 1 || selected_square > 9 || board[selected_square - 1] != '1' + selected_square - 1) {
            selected_square = get_user_input(current_player); // Get input from the current player
        }

        board[selected_square - 1] = (current_player == 1) ? 'X' : 'O';
        total_moves++;

        winner = check_for_winner(board);
        if (winner == '\0') {
            current_player = 3 - current_player; // Switch player
        }
    }

    display_board(board); // Display the final board
    if (winner != '\0') {
        ft_putstr("Congratulations Player ");
        ft_putchar(winner == 'X' ? '1' : '2');
        ft_putstr(", you've won the game!\n");
    } else {
        ft_putstr("It's a draw! Well played both!\n");
    }

    return 0;
}