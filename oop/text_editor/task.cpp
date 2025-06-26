#include "task.h"
#include "logged_command_wrapper.h"
#include<string>
#include<iostream>
CommandLoggerVisitor::CommandLoggerVisitor(std::ostream& logStream)
:logStream_(logStream){};


/* Курсор влево */
class MoveCursorLeftCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(cursorPosition > 0)
        {
            cursorPosition--;
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveCursorLeftCommand(*this);
    }
};

/* Курсор вправо */
class MoveCursorRightCommand : public ICommand {
    public:
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(cursorPosition != buffer.size() - 1)
        {
            cursorPosition++;
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveCursorRightCommand(*this);
    }
};

/* Курсор вверх */
class MoveCursorUpCommand : public ICommand {
    public:
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        size_t cursor = cursorPosition - 1;
        //std::cout << cursor << std::endl;
        if(cursor != 0)
        {
            while(cursor != 0 && buffer[cursor] != '\n')
            {
                cursor--;
            }
            int size = cursorPosition - cursor - 1;
            //std::cout << size << std::endl;

            if(cursor != 0)
            {
                size_t string_begin = cursor - 1;
                while(string_begin != 0 && buffer[string_begin] != '\n')
                {
                    string_begin--;

                }
                if(string_begin == 0)
                {
                cursorPosition = string_begin + size;
                }
                else{
                    cursorPosition = string_begin + size + 1;
                }
            }
        }
    }


    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveCursorUpCommand(*this);
    }


};

/* Курсор вниз */
class MoveCursorDownCommand : public ICommand {
    public:
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        size_t cursor = cursorPosition;
        //std::cout << cursor << std::endl;
        int size = 0;
        if(cursor != buffer.size() - 1)
        {
            while(cursor > 0 && buffer[cursor] != '\n')
            {
                cursor--;
                size++;
            }
            //std::cout << size << std::endl;

            if(cursor != buffer.size() - 1)
            {
                size_t string_begin = cursor + 1;
                while(string_begin != buffer.size() - 1 && buffer[string_begin] != '\n')
                {
                    string_begin++;
                }
                if(string_begin == buffer.size() - 1)
                {
                cursorPosition = string_begin + size;
                }
                else{
                    cursorPosition = string_begin + size + 1;
                }
            }
        }
    }

        void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveCursorDownCommand(*this);
        }
};

/* Выделить текст */
class SelectTextCommand : public ICommand {
    public:
    SelectTextCommand(size_t selection)
    :selection_(selection){};

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        editor.SelectText(cursorPosition, cursorPosition + this->selection_);
    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitSelectCommand(*this);
    }

    private:
        size_t selection_;
    
};

/* Ввести текст */
class InsertTextCommand : public ICommand {
    public:
    InsertTextCommand(std::string text)
    : text_(text){};
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(editor.HasSelection() == true)
        {
            size_t l = editor.GetSelection().first;
            size_t r = editor.GetSelection().second;
            std::string s1 = buffer.substr(0,l);
            std::string s2 = buffer.substr(r, buffer.size() - r);
            buffer = s1 + text_ + s2;
        }
        else{
            //std::cout << "hi\n";
            std::string s1 = buffer.substr(0, cursorPosition);
            std::string s2 = buffer.substr(cursorPosition, buffer.size() - cursorPosition);
            buffer = s1 + text_ + s2;
        }
        cursorPosition += text_.size();
        editor.UnselectText();
    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitInsertTextCommand(*this);
    }
    private:
        std::string text_;

};

/* Удалить текст */
class DeleteTextCommand : public ICommand {
    public:
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        buffer.erase();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitDeleteTextCommand(*this);
    }

};

/* Скопировать текст */
class CopyTextCommand : public ICommand {
    public:
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
    
        if(editor.HasSelection())
        {
            clipboard = buffer.substr(editor.GetSelection().first, editor.GetSelection().second - editor.GetSelection().first);
            editor.UnselectText();
        }
        else
        {
        clipboard = buffer[cursorPosition - 1];
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitCopyTextCommand(*this);
    }
};

/* Вставить скопированный текст */
class PasteTextCommand : public ICommand {
    public:
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
            if(editor.HasSelection() == 1)
            {
            size_t l = editor.GetSelection().first;
            size_t r = editor.GetSelection().second;
            std::string s1;
            std::string s2;
            if(r == buffer.size() && l < buffer.size() - 1)
            {
                s1 = buffer.substr(0,l);
                s2 = "";
            }
            else
            {
            s1 = buffer.substr(0,l);
            s2 = buffer.substr(r, buffer.size() - r);
            }
            buffer = s1 + clipboard + s2;
            editor.UnselectText();

            
        }
        else{
            std::string s1 = buffer.substr(0, cursorPosition);
            std::string s2 = buffer.substr(cursorPosition, buffer.size() - cursorPosition);
            buffer = s1 + clipboard + s2;
        }
        cursorPosition += clipboard.size();
        editor.UnselectText();
    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitPasteTextCommand(*this);
    }

};

/* Привести выделенный текст в ВЕРХНИЙ регистр */
class UppercaseTextCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
    if(editor.HasSelection())
    {
        //std::cout << "hiyy\n";
        for(size_t i = editor.GetSelection().first; i < editor.GetSelection().second;i++)
        {
            buffer[i] = toupper(buffer[i]);
        }
    }
    else{
        buffer[cursorPosition] = toupper(buffer[cursorPosition]);
        }
    }



    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitUppercaseTextCommand(*this);
    }
};

/* Привести выделенный текст в нижний регистр */
class LowercaseTextCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
    if(editor.HasSelection())
    {
        for(size_t i = editor.GetSelection().first; i < editor.GetSelection().second;i++)
        {
            buffer[i] = tolower(buffer[i]);
        }
    }
    else{
        buffer[cursorPosition] = tolower(buffer[cursorPosition]);
    }
    }



    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitLowercaseTextCommand(*this);
    }
};

/* Перенести курсор в конец строки */
class MoveToEndCommand : public ICommand {
    public:
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        while(cursorPosition < buffer.size() && buffer[cursorPosition] != '\n')
        {
            cursorPosition++;//pashalka :: killer nooobov eto ya
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveToEndCommand(*this);
    }
};

/* Перенести курсор в начало строки */
class MoveToStartCommand : public ICommand {
    public:
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        while (cursorPosition > 0 && buffer[cursorPosition - 1] != '\n') {
            --cursorPosition;
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveToStartCommand(*this);
    }
};

/* Удалить часть строки, начиная от позиции курсора до первого пробела или конца строки */
class DeleteWordCommand : public ICommand {
    public:
        void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
            size_t r = cursorPosition;
            while(r < buffer.size() && buffer[r] != '\n' && buffer[r] != ' ')
            {
                r++;
            }

            std::string s1 = buffer.substr(0, cursorPosition);
            std::string s2 = buffer.substr(r, buffer.size() - r);
            buffer = s1 + s2;
            //std::cout << editor.GetText() << std::endl;
            editor.UnselectText();
        }
        void AcceptVisitor(CommandVisitor& visitor) override{
            visitor.VisitDeleteWordCommand(*this);
        }
};

/* Макрос */
class MacroCommand : public ICommand {
    public:
        MacroCommand(std::list<CommandPtr> subcommands)
        :subcommands_gege(subcommands){};
        void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
            for(auto& it: subcommands_gege)
            {
                (*it).Apply(buffer, cursorPosition, clipboard, editor);
            }   
        }     

        void AcceptVisitor(CommandVisitor& visitor) override{
            for (auto& command : subcommands_gege) {
                (*command).AcceptVisitor(visitor);
            }
        }

    private:
        std::list<CommandPtr> subcommands_gege;
};



using CommandPtr = std::shared_ptr<ICommand>;

CommandBuilder::CommandBuilder():
    logStreamPtr_(nullptr){};



CommandPtr CommandBuilder::build() {
    CommandPtr key_t;
    if(this->type_ == Type::MoveCursorLeft)
    {
        key_t = std::make_shared<MoveCursorLeftCommand>(MoveCursorLeftCommand());
    }
    if(this->type_ == Type::MoveCursorRight)
    {
        key_t = std::make_shared<MoveCursorRightCommand>(MoveCursorRightCommand());
    }
    if(this->type_ == Type::MoveCursorDown)
    {
        key_t = std::make_shared<MoveCursorDownCommand>(MoveCursorDownCommand());
    }
    if(this->type_ == Type::MoveCursorUp)
    {
        key_t = std::make_shared<MoveCursorUpCommand>(MoveCursorUpCommand());
    }
    if(this->type_ == Type::SelectText)
    {
        key_t = std::make_shared<SelectTextCommand>(SelectTextCommand(this->selectionSize_));
    }
    if(this->type_ == Type::InsertText)
    {
        key_t = std::make_shared<InsertTextCommand>(InsertTextCommand(this->text_));
    }
    if(this->type_ == Type::DeleteText)
    {
        key_t = std::make_shared<DeleteTextCommand>(DeleteTextCommand());
    }
    if(this->type_ == Type::CopyText)
    {
        key_t = std::make_shared<CopyTextCommand>(CopyTextCommand());
    }
    if(this->type_ == Type::PasteText)
    {
        key_t = std::make_shared<PasteTextCommand>(PasteTextCommand());
    }
    if(this->type_ == Type::UppercaseText)
    {
        key_t = std::make_shared<UppercaseTextCommand>(UppercaseTextCommand());
    }
    if(this->type_ == Type::LowercaseText)
    {
        key_t = std::make_shared<LowercaseTextCommand>(LowercaseTextCommand());
    }
    if(this->type_ == Type::MoveToEnd)
    {
        key_t = std::make_shared<MoveToEndCommand>(MoveToEndCommand());
    }
    if(this->type_ == Type::MoveToStart)
    {
        key_t = std::make_shared<MoveToStartCommand>(MoveToStartCommand());
    }
    if(this->type_ == Type::DeleteWord)
    {
        key_t = std::make_shared<DeleteWordCommand>(DeleteWordCommand());
    }

    if(this->type_ == Type::Macro) {
        key_t = std::make_shared<MacroCommand>(MacroCommand(this->subcommands_));
    }
    if(logStreamPtr_ != nullptr)
    {
        key_t = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_, key_t));
    }
    return key_t;
}


CommandBuilder &CommandBuilder::WithType(CommandBuilder::Type type) {
    this->type_ = type;
    return *this;
}


CommandBuilder &CommandBuilder::SelectionSize(size_t selectionSize) {
    this->selectionSize_ = selectionSize;
    return *this;
}


CommandBuilder &CommandBuilder::Text(std::string text) {
    this->text_ = text;
    return *this;
}


CommandBuilder &CommandBuilder::LogTo(std::ostream &logStream) {
    this->logStreamPtr_ = &logStream;
    return *this;
    
}


CommandBuilder &CommandBuilder::AddSubcommand(CommandPtr subcommand) {
    this->subcommands_.push_back(subcommand);
    return *this;
}


// Logger Visitor

void CommandLoggerVisitor::VisitMoveCursorLeftCommand(MoveCursorLeftCommand &command) {
    this->logStream_ << 'h';
}

void CommandLoggerVisitor::VisitMoveCursorRightCommand(MoveCursorRightCommand &command) {
    this->logStream_ << "l";
}


void CommandLoggerVisitor::VisitMoveCursorUpCommand(MoveCursorUpCommand &command) {
    this->logStream_ << "k";
}


void CommandLoggerVisitor::VisitMoveCursorDownCommand(MoveCursorDownCommand &command) {
    this->logStream_ << "j";
}


void CommandLoggerVisitor::VisitSelectCommand(SelectTextCommand &command) {
    this->logStream_ << "v";
}


void CommandLoggerVisitor::VisitInsertTextCommand(InsertTextCommand &command) {
    this->logStream_ << "i";
}


void CommandLoggerVisitor::VisitDeleteTextCommand(DeleteTextCommand &command) {
    this->logStream_ << "d";
}


void CommandLoggerVisitor::VisitCopyTextCommand(CopyTextCommand &command) {
    this->logStream_ << "y";
}


void CommandLoggerVisitor::VisitPasteTextCommand(PasteTextCommand &command) {
    this->logStream_ << "p";
}


void CommandLoggerVisitor::VisitUppercaseTextCommand(UppercaseTextCommand &command) {
    this->logStream_ << "U";
}


void CommandLoggerVisitor::VisitLowercaseTextCommand(LowercaseTextCommand &command) {
    this->logStream_ << "u";
}


void CommandLoggerVisitor::VisitMoveToEndCommand(MoveToEndCommand &command) {
    this->logStream_ << "$";
}


void CommandLoggerVisitor::VisitMoveToStartCommand(MoveToStartCommand &command) {
    this->logStream_ << "0";
}


void CommandLoggerVisitor::VisitDeleteWordCommand(DeleteWordCommand &command) {
    this->logStream_ << "dE";
}
