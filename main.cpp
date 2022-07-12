#include <iostream>
#include <string>

using namespace std;

struct InputBuffer {
    string buffer;
    size_t bufferLength{};
    ssize_t inputLength{};
};

InputBuffer *new_input_buffer();

void print_prompt();

void read_input(InputBuffer *inputBuffer);

void close_input_buffer(InputBuffer *inputBuffer);

int main(int argc, char *argv[]) {
    InputBuffer *inputBuffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(inputBuffer);

        if (inputBuffer->buffer == ".exit") {
            close_input_buffer(inputBuffer);
            exit(EXIT_SUCCESS);
        } else {
            cout << "Unrecognized command " << inputBuffer->buffer << "\n";
        }
    }
}

InputBuffer *new_input_buffer() {
    auto inputBuffer = new InputBuffer[sizeof(InputBuffer)];
    inputBuffer->bufferLength = 0;
    inputBuffer->inputLength = 0;

    return inputBuffer;
}

void print_prompt() {
    cout << "mydb > ";
}

void read_input(InputBuffer *inputBuffer) {
    getline(cin, inputBuffer->buffer);

    if (inputBuffer->buffer.empty()) {
        cout << "Error reading input\n";
        exit(EXIT_FAILURE);
    }
}

void close_input_buffer(InputBuffer *inputBuffer) {
    delete inputBuffer;
}
