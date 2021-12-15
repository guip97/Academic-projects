#include <iostream>

#define LOG(x) cout << x << endl

using namespace std;

class String
{
public:

    String() = default;

    String(const char* String)
    {
        /** Pointer arithmetics */
        for (const char* c = String; *c != '\0'; c++)
        {
            Size++;
        }

        Data = new char[Size];

        for (int i = 0; i < Size; i++)
        {
            Data[i] = String[i];
        }
    }

    /** Copy constructor */
    String(const String& Copy)
    {
        Size = Copy.Size;

        Data = new char[Size];

        for (int i = 0; i < Size; i++)
        {
            Data[i] = Copy.Data[i];
        }
    }

    /** Move constructor */
    String(String&& Move) noexcept
    {
        Size = Move.Size;

        Data = Move.Data;

        Move.Size = 0;
        Move.Data = nullptr;
    }

    friend ostream& operator<< (ostream& os, const String& s)
    {
        for (int i = 0; i < s.Size; i++)
        {
            os << s.Data[i];
        }

        return os;
    }

    /** Copy assignment */
    void operator=(String& s)
    {
        if (this != &s)
        {
            /** Have to reallocate string if sizes don't match */
            if (this->Size != s.Size)
            {
                delete[] Data;
                this->Size = s.Size;
            }

            Data = new char[Size];

            for (int i = 0; i < Size; i++)
            {
                Data[i] = s.Data[i];
            }
        }
    }

    /** Move assignment */
    void operator=(String&& s) noexcept
    {
        this->Size = s.Size;

        Data = s.Data;

        s.Size = 0;
        s.Data = nullptr;
    }

    void operator+=(const String& s)
    {
        this->append(s);
    }

    void operator+=(const String&& s)
    {
        this->append(s);
    }

    String operator+(const String& s)
    {
        String out(*this);
        out.append(s);

        return out;
    }

    String operator+(const String&& s)
    {
        String out(*this);
        out.append(s);

        return out;
    }

    bool operator>(const String& B)
    {
        int MinSize = B.Size > this->Size ? this->Size : B.Size;

        for (int i = 0; i < MinSize; i++)
        {
            if (this->Data[i] != B.Data[i])
            {
                return this->Data[i] > B.Data[i];
                break;
            }
        }

        return false;
    }

    bool operator<(const String& B)
    {
        int MinSize = B.Size > this->Size ? this->Size : B.Size;

        for (int i = 0; i < MinSize; i++)
        {
            if (this->Data[i] != B.Data[i])
            {
                return B.Data[i] > this->Data[i];
                break;
            }
        }

        return false;
    }

    void append(char c)
    {
        char* temp = new char[Size + 1];

        /** Create a copy of the array */
        for (int i = 0; i < Size; i++)
        {
            temp[i] = Data[i];
        }

        temp[Size] = c;

        delete[] Data;
        Size++;
        Data = temp;
        temp = nullptr;
    }

    void append(const char* String)
    {
        int SubSize = 0;
        for (const char* c = String; *c != '\0'; c++)
        {
            SubSize++;
        }

        char* temp = new char[SubSize + this->Size];

        /** Filling temp array with initial values */
        for (int i = 0; i < Size; i++)
        {
            temp[i] = Data[i];
        }

        /** Appending new sub string */
        for (int i = Size; i < SubSize + this->Size; i++)
        {
            temp[i] = String[i - Size];
        }

        delete[] Data;
        Size += SubSize;

        Data = temp;
        temp = nullptr;
    }

    void append(const String& String)
    {
        char* temp = new char[String.Size + this->Size];

        /** Filling temp array with initial values */
        for (int i = 0; i < Size; i++)
        {
            temp[i] = Data[i];
        }

        /** Appending new sub string */
        for (int i = Size; i < String.Size + this->Size; i++)
        {
            temp[i] = String.Data[i - Size];
        }

        delete[] Data;
        Size += String.Size;

        Data = temp;
        temp = nullptr;
    }

    /** Insert at the given index */
    void insert(char* SubString, int index)
    {
        if (index >= 0 && index < this->Size)
        {
            if (index == this->Size - 1)
            {
                append(SubString);
            }
            else if (index == 0)
            {
                String s(SubString);
                s.append(this->Data);

                delete[] this->Data;

                this->Size = s.Size;
                this->Data = s.Data;

                s.Data = nullptr;
                s.Size = 0;
            }
            else
            {
                int SubSize = 0;
                for (char* c = SubString; *c != '\0'; c++)
                {
                    SubSize++;
                }

                char* temp = new char[SubSize + this->Size];
                int i = 0;
                for (; i < index; i++)
                {
                    temp[i] = this->Data[i];
                }

                for (; i < index + SubSize; i++)
                {
                    temp[i] = SubString[i - index];
                }

                for (; i < index + SubSize + Size - 1; i++)
                {
                    temp[i] = this->Data[i - SubSize];
                }

                delete[] this->Data;

                this->Data = temp;
                this->Size += SubSize;

                temp = nullptr;
            }
        }
    }

    void insert(const String& s, int index)
    {
        this->insert(s.Data, index);
    }

    void erase(int start, int end)
    {
        if (start > end)
        {
            int temp = end;
            end = start;
            start = temp;
        }

        if (start < 0 || end > this->Size - 1)
        {
            return;
        }
        else
        {
            /** Swap start and end when */

            int NewSize = this->Size - (end - start + 1);

            char* temp = new char[NewSize];
            for (int i = 0; i < start; i++)
            {
                temp[i] = Data[i];
            }

            for (int i = end + 1; i < this->Size; i++)
            {
                temp[i - (end - start + 1)] = Data[i];
            }

            delete[] Data;
            this->Data = temp;
            this->Size = NewSize;

            temp = nullptr;
        }
    }

    void reverse()
    {
        for (int i = 0; i < Size / 2; i++)
        {
            char temp = Data[Size - i - 1];
            Data[Size - i - 1] = Data[i];
            Data[i] = temp;
        }
    }

    int size()
    {
        return Size;
    }

    ~String()
    {
        delete[] Data;
    }

private:

    char* Data = nullptr;
    int Size = 0;
};

int main()
{
    String s("Hello,");
    s += String(" World!");

    cout << s;
}