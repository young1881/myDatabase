#include <iostream>
#include <string>

using namespace std;

enum MetaCommandResult {
    META_COMMAND_SUCCESS, META_COMMAND_UNRECOGNIZED
};

enum PrepareResult {
    PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT
};

enum StatementType {
    INSERT, SELECT
};

struct InputBuffer {
    string buffer;
    size_t bufferLength{};
    ssize_t inputLength{};
};

struct Statement {
    StatementType type;
};

InputBuffer *new_input_buffer();

void print_prompt();

void read_input(InputBuffer *inputBuffer);

MetaCommandResult do_meta_command(InputBuffer *inputBuffer);

PrepareResult prepare_statement(InputBuffer *inputBuffer, Statement *statement);

void execute_statement(Statement *statement);

void close_input_buffer(InputBuffer *inputBuffer);

int main(int argc, char *argv[]) {
    InputBuffer *inputBuffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(inputBuffer);

        // Non-SQL statements like .exit are called “meta-commands”.
        if (inputBuffer->buffer[0] == '.') {
            switch (do_meta_command(inputBuffer)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED):
                    cout << "Unrecognized command" << inputBuffer->buffer
                         << ".\n";
                    continue;
            }
        }

        Statement statement{};
        switch (prepare_statement(inputBuffer, &statement)) {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                cout << "Unrecongnized keyword at the start of "
                     << inputBuffer->buffer << ".\n";
                continue;
        }

        execute_statement(&statement);
        cout << "Executed.\n";
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

MetaCommandResult do_meta_command(InputBuffer *inputBuffer) {
    if (inputBuffer->buffer == ".exit") {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED;
    }
}

PrepareResult prepare_statement(InputBuffer *inputBuffer,
                                Statement *statement) {
    if (inputBuffer->buffer.substr(0, 6) == "insert") {
        statement->type = INSERT;
        return PREPARE_SUCCESS;
    }
    if (inputBuffer->buffer == "select") {
        statement->type = SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement *statement) {
    switch (statement->type) {
        case (INSERT):
            cout << "This is where we would do an insert.\n";
            break;
        case (SELECT):
            cout << "This is where we would do a select.\n";
            break;
    }
}

void close_input_buffer(InputBuffer *inputBuffer) {
    delete inputBuffer;
}
