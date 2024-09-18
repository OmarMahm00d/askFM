#include <iostream>
#include <tuple>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>
#include <limits>
#include <cstring>
using namespace std;

struct Handling
{
    template <size_t N>
    void hundle_word(char (&buffer)[N])
    {
        if (buffer[0] == 0)
        {
            throw invalid_argument("Error: cannot be empty!\n");
        }

        if (buffer[N-2] != 0)
        {
            throw length_error("Error: invalid input, too long!\n");
        }

        for (auto &i : buffer)
        {
            if (i == ' ')
            {
                throw invalid_argument("Error: invalid input, please do not use spaces.\n");
            }
        }
    }

    // Function to check the character
    // is an alphabet or not
    bool isChar(char c)
    {
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    }

    // Function to check the character
    // is an digit or not
    bool isDigit(const char c)
    {
        return (c >= '0' && c <= '9');
    }

    template <size_t N>
    void hundle_email(char (&buffer)[N])
    {
        //check the email address size
        if (buffer[N-2] != 0)
        {
            throw length_error("Error: invalid email, too long!\n");
        }

        // Check the first character
        // is an alphabet or not
        if (!isChar(buffer[0]))
            throw invalid_argument("Error: Invalid email.\n");

        // Variable to store position
        // of At and Dot
        int At = -1, Dot = -1;
        // Traverse over the email id
        // string to find position of
        // Dot and At
        for (int i = 0; i < N; i++)
        {
            //if string is finished
            if (buffer[i] == 0)
                break;
            // If the character is '@'
            if (buffer[i] == '@')
                At = i;

            // If character is '.'
            else if (buffer[i] == '.')
                Dot = i;
        }

        // If At or Dot is not present
        if (At == -1 || Dot == -1)
            throw invalid_argument("Error: Invalid email.\n");

        // If Dot is present before At
        if (At > Dot)
            throw invalid_argument("Error: Invalid email.\n");

        // If Dot is present at the end
        if (buffer[Dot+1] == 0)
            throw invalid_argument("Error: Invalid email.\n");
    }
};

struct DataBase

{
    ifstream read;
    ofstream write;
    string questions_path = "server/questions.txt";
    string users_path = "server/users.txt";

    // sellect all info and load it into table
    void select_all_users_info(vector<tuple<int, string, string, string, string, bool>> &table)
    {
        read.open(users_path);

        if (read.fail())
        {
            cout << "Error: can't open file. " << endl;
            return;
        }

        vector<string> lines;
        int i = 0;
        while (lines.push_back(""), getline(read, lines[i]))
        {
            istringstream iss(lines[i++]);
            tuple<int, string, string, string, string, bool> attributes_tuple;
            int attr1;
            string attr2, attr3, atrr4, attr5;
            bool attr6;
            char ignore;

            iss >> attr1 >> ignore;
            getline(iss, attr2, ',');
            getline(iss, attr3, ',');
            getline(iss, atrr4, ',');
            getline(iss, attr5, ',');
            iss >> attr6;

            attributes_tuple = make_tuple(attr1, attr2, attr3, atrr4, attr5, attr6);

            table.push_back(attributes_tuple);
        }

        if (read.bad())
            cout << " Error: error in reading attributes.\n";

        read.close();
        return;
    }

    void sellect_all_questions_info(vector<tuple<int, int, int, string, string, vector<tuple<int, int, string, string>>>> &table)
    {
        read.open(questions_path);
        if (read.fail())
        {
            cout << "Error: can't open file. " << endl;
            return;
        }

        // parsing attributes
        vector<string> lines;
        int i = 0;
        while (lines.push_back(""), getline(read, lines[i]))
        {
            istringstream iss(lines[i++]);
            tuple<int, int, int, string, string, vector<tuple<int, int, string, string>>> attributes_tuple;

            int attr1;
            int attr2, attr3;
            string attr4, attr5;
            int attr6;
            vector<tuple<int, int, string, string>> attr7;
            char ignore;

            iss >> attr1 >> ignore;
            iss >> attr2 >> ignore;
            iss >> attr3 >> ignore;
            getline(iss, attr4, ',');
            getline(iss, attr5, ',');
            iss >> attr6 >> ignore;
            for (int i = 0; i < attr6; i++)
            {
                int attr7_1, attr7_2;
                string attr7_3, attr7_4;
                iss >> attr7_1 >> ignore;
                iss >> attr7_2 >> ignore;
                getline(iss, attr7_3, ',');
                getline(iss, attr7_4, ',');
                attr7.push_back(make_tuple(attr7_1, attr7_2, attr7_3, attr7_4));
            }
            attributes_tuple = make_tuple(attr1, attr2, attr3, attr4, attr5, attr7);

            table.push_back(attributes_tuple);
        }

        if (read.bad())
            cout << "Error: error in reading attributes.\n";

        read.close();
        return;
    }

    // users manipulation functions
    bool store_user(const tuple<int, string, string, string, string, bool> &attributes_tuple)
    {
        // open the file
        write.open(users_path, ios::app);
        if (write.fail())
        {
            cout << "Error: can't open file.\n";
            return false;
        }

        // add tuple
        auto &[attr1, attr2, attr3, attr4, attr5, attr6] = attributes_tuple;
        write << attr1 << ',' << attr2 << ',' << attr3 << ',' << attr4 << ',' << attr5 << ',' << attr6 << '\n';
        if (write.bad())
        {
            cout << "Error: error in writing on file.\n";
            return false;
        }

        // close the file
        write.close();

        return true;
    }

    auto get_user_info_by_user_name(const std::string &user_name)
    {
        pair<bool, tuple<int, string, string, string, string, bool>> requested_info = make_pair(0, make_tuple(-1, "", "", "", "", 0));
        read.open(users_path);

        if (read.fail())
        {
            cout << "Error: can't open file. " << endl;
            return requested_info;
        }

        string line;
        while (getline(read, line))
        {
            istringstream iss(line);
            int attr1;
            string attr2_uname, attr3, attr4, attr5;
            bool attr6;

            iss >> attr1;
            iss.ignore();
            getline(iss, attr2_uname, ',');

            if (!(attr2_uname == user_name))
                continue;

            getline(iss, attr3, ',');
            getline(iss, attr4, ',');
            getline(iss, attr5, ',');
            iss >> attr6;

            if (read.bad())
            {
                cout << "Error: error in reading attributes.\n";
                return requested_info;
            }

            requested_info = make_pair(true, make_tuple(attr1, attr2_uname, attr3, attr4, attr5, attr6));
            break;
        }

        read.close();
        return requested_info;
    }

    // questions manipulation functions
    bool add_new_question_line(const int &q_id, const int &from_uid, const int &to_uid, const string &question)
    {
        string ans{""};
        int t_num = 0;

        write.open(questions_path, ios::app);
        if (write.fail())
        {
            cout << "Error: can't open file.\n";
            return false;
        }

        write << q_id << "," << from_uid << "," << to_uid << "," << question << "," << ans << "," << t_num << endl;

        if (write.bad())
        {
            cout << "Error: error in writing on file.\n";
            return false;
        }

        write.close();
        return true;
    }

    bool store_new_thread(const int &qid, const tuple<int, int, string, string> &thrd)
    {
        // logic of updating question
        return true;
    }

    bool update_question_line(tuple<int, int, int, string, string, vector<tuple<int, int, string, string>>> modifyed_line)
    {
        // logic of updating question
        return true;
    }

    bool delete_question_line(const int &id)
    {
        // logic of deleting
        return true;
    }

    bool delete_thread(const int &parent_q_id, const int &thrd_id)
    {
        // logic of deleting thread
        return true;
    }
};

struct User_Info
{
    int user_id{-1};
    string user_name{""};
    string password{""};
    string name{""};
    string email{""};
    bool AQ{false};

    User_Info() {}

    User_Info(int uid, string unm, string pswd, string nm, string eml, bool aq) : user_id(uid), user_name(unm), password(pswd), name(nm), email(eml), AQ(aq)
    {
    }

    User_Info(tuple<int, string, string, string, string, bool> info) : user_id(get<0>(info)), user_name(get<1>(info)), password(get<2>(info)), email(get<3>(info)), name(get<4>(info)), AQ(get<5>(info))
    {
    }

    void print()
    {
        cout << "User ID: " << user_id << endl;
        cout << "User Name: " << user_name << endl;
        cout << "Password: " << password << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Anonomus Question: " << (AQ ? "Yes" : "No") << endl;
    }
};

struct Thread
{
    int ID{-1};
    int from_user_id{-1};
    string content{""};
    string answer{""};

    Thread(int id, int from, string content, string answer_question) : ID(id), from_user_id(from), content(content), answer(answer_question) {}

    void print()
    {
        cout << "Thread ID: " << ID << "\t";
        if (from_user_id != -1)
            cout << " From User ID: " << from_user_id << "\t";
        cout << " Question: " << content << endl;
        if (answer != "")
            cout << "  Answer: " << answer << endl;
    }
};

struct Question
{
    int ID{-1};
    int from_user_id{-1};
    int to_user_id{-1};
    string content{""};
    string answer{""};
    vector<Thread> threads;

    Question() {}
    Question(int id, int from, int to, string content, string answer, vector<Thread> thrds) : ID(id), from_user_id(from), to_user_id(to), content(content), answer(answer), threads(thrds) {}
    Question(int id, int from, int to, string content, string answer, vector<tuple<int, int, string, string>> thrds) : ID(id), from_user_id(from), to_user_id(to), content(content), answer(answer)
    {
        for (auto &thrd : thrds)
        {
            auto &[t_id, from_id, content, answer] = thrd;
            threads.push_back(Thread(t_id, from_id, content, answer));
        }
    }

    void print()
    {
        cout << "Question ID: " << ID << "\t";
        if (from_user_id != -1)
            cout << " From User ID: " << from_user_id << "\t";
        if (to_user_id != -1)
            cout << " To User ID: " << to_user_id << "\t";
        cout << " Question: " << content << endl;
        if (answer != "")
            cout << "  Answer: " << answer << endl;
        if (threads.size())
        {
            cout << "Threads: " << endl;
            for (auto &thrd : threads) // print threads
            {
                thrd.print();
            }
        }
    }

    void print_without_thread()
    {
        cout << "Question ID: " << ID << "\t";
        if (from_user_id != -1)
            cout << " From User ID: " << from_user_id << "\t";
        if (to_user_id != -1)
            cout << " To User ID: " << to_user_id << "\t";
        cout << " Question: " << content << endl;
        if (answer != "")
            cout << "  Answer: " << answer << endl;
    }

    void push_thread(const Thread &thrd)
    {
        threads.push_back(thrd);
    }

    void delete_thread(const int &index)
    {
        auto it = threads.begin();
        it += index;
        threads.erase(it);

        return;
    }
};

struct Server
{
    DataBase db;
    set<int> uIDs;
    set<int> qIDs;
    set<string> user_names;
    vector<User_Info> users_info;
    vector<Question> questions;

    Server()
    {
        vector<tuple<int, string, string, string, string, bool>> users_data;
        vector<tuple<int, int, int, string, string, vector<tuple<int, int, string, string>>>> questions_data;

        db.select_all_users_info(users_data);
        db.sellect_all_questions_info(questions_data);

        // initialization
        int sz = users_data.size();
        for (int i = 0; i < sz; i++)
        {
            int uid;
            string unm, pswd, nm, email;
            bool aq;

            tie(uid, unm, pswd, nm, email, aq) = users_data[i];

            User_Info user{uid, unm, pswd, nm, email, aq};

            users_info.push_back(user);
            uIDs.insert(uid);
            user_names.insert(unm);
        }

        // continue initialization
        sz = questions_data.size();
        for (int i = 0; i < sz; i++)
        {
            int qid, from_uid, to_uid, tnum, tid, t_from_uid;
            string content, answer, t_contnet, t_answer;
            vector<tuple<int, int, string, string>> threads;

            tie(qid, from_uid, to_uid, content, answer, threads) = questions_data[i];

            Question question{qid, from_uid, to_uid, content, answer, threads};

            questions.push_back(question);
            qIDs.insert(qid);
            for (auto &t : threads)
                qIDs.insert(get<0>(t));
        }
    }

    // user functions
    int gen_user_id()
    {
        int i = 0;
        while (++i)
        {
            auto [it, is_inserted] = uIDs.insert(i); // try to insert id
            if (!is_inserted)                        // faild to insert id
                continue;
            break; // id is inserted
        }
        return i;
    }

    void push_back_user_info(tuple<int, string, string, string, string, bool> &record)
    {
        users_info.push_back(User_Info(record));
    }

    bool add_user(tuple<string, string, string, string, bool> &info)
    {
        // generate new id for new user
        int new_id = gen_user_id();
        auto new_record = tuple_cat(make_tuple(new_id), info);

        // store in Database
        if (!db.store_user(new_record))
            return false;

        // update server information
        push_back_user_info(new_record);

        return true;
    }

    auto insert_new_thread(const int &qid, const int &from_usr_id, const int &to_usr_id, const string &question)
    {
        int sz = questions.size();
        for (int i = 0; i < sz; i++)
        {
            if (questions[i].ID == qid)
            {
                int new_id = gen_question_id();

                if (!db.store_new_thread(qid, make_tuple(new_id, to_usr_id, question, "")))
                {
                    qIDs.erase(new_id);
                    return make_pair(false, -1);
                }

                questions[i].threads.push_back(Thread(qid, to_usr_id, question, ""));

                return make_pair(true, qid);
            }
        }

        cout << "Error: Cannot find thread id." << endl;
        return make_pair(false, -1);
    }

    bool check_user_name(const string &user_name)
    {
        auto [it, is_inserted] = user_names.insert(user_name);
        if (is_inserted)
            return 1;
        return 0;
    }

    pair<bool, User_Info> authentication(const string &user_name, const string &password)
    {
        // return is_authenticated, matched_user_info
        pair<bool, tuple<int, string, string, string, string, bool>> info = db.get_user_info_by_user_name(user_name);
        bool is_found = info.first;
        tuple<int, string, string, string, string, bool> matched_record = info.second;

        string selected_user_password = get<2>(matched_record);
        if (is_found && (selected_user_password == password))
        {
            bool is_valid_login = true;
            return make_pair(is_valid_login, User_Info(matched_record));
        }

        return make_pair(false, User_Info());
    }

    bool is_valid_user_id(int id)
    {
        return uIDs.count(id);
    }

    User_Info get_user_info_by_id(int id)
    {
        for (auto &usr_info : users_info)
        {
            if (usr_info.user_id == id)
                return usr_info;
        }
        cout << "Erorr: unkown id\n";
        return User_Info();
    }

    // question functions
    int gen_question_id()
    {
        int sz = qIDs.size();
        for (int i = 1; i < sz; i++)
        {
            auto [it, is_inserted] = qIDs.insert(i);
            if (!is_inserted)
                continue;
            return i;
        }

        return sz;
    }

    bool is_valid_question_id(int id)
    {
        return qIDs.count(id);
    }

    Question get_question_by_index(const int &index)
    {
        if (index >= questions.size())
        {
            return Question();
        }

        Question q{questions[index]};

        // hide user's info
        if (get_user_info_by_id(q.from_user_id).AQ)
            q.from_user_id = -1;
        if (get_user_info_by_id(q.to_user_id).AQ)
            q.to_user_id = -1;
        for (auto &thread : q.threads)
        {
            if (get_user_info_by_id(thread.from_user_id).AQ)
                thread.from_user_id = -1;
        }

        return q;
    }

    Question get_question_by_id(const int &id)
    {
        for (auto &question : questions)
        {
            if (question.ID == id)
                return question;
        }
        cout << "Erorr: unkown id\n";
        return Question();
    }

    int get_question_index(int id)
    {
        int i = 0;
        for (auto &question : questions)
        {
            if (question.ID == id)
                return i;
            i++;
        }
        return -1;
    }

    bool get_sent_recieved_questions(int uid, vector<Question> &sent, vector<Question> &recieved)
    {
        bool is_vaild_uid = is_valid_user_id(uid);
        if (!is_vaild_uid)
            return false;

        auto user_info = get_user_info_by_id(uid);

        int sz = questions.size();
        for (int i = 0; i < sz; i++)
        {
            Question q = questions[i];
            if (q.from_user_id == uid)
            {
                if (user_info.AQ)
                    q.from_user_id = -1; // hide user

                sent.push_back(q);
            }

            if (q.to_user_id == uid)
            {
                if (user_info.AQ)
                    q.to_user_id = -1; // hide user

                recieved.push_back(q);
            }
        }
        return true;
    }

    bool answer_question(const string &ans, const int &qid)
    {
        for (auto &q : questions)
        {
            if (q.ID == qid)
            {
                q.answer = ans;

                // update answers
                vector<tuple<int, int, string, string>> rq_thread_tuples;
                for (auto &thread : q.threads)
                {
                    auto tuple = make_tuple(thread.ID, thread.from_user_id, thread.content, thread.answer);
                    rq_thread_tuples.push_back(tuple);
                }

                auto rq_tuple = make_tuple(q.ID, q.from_user_id, q.to_user_id, q.content, q.answer, rq_thread_tuples);

                db.update_question_line(rq_tuple);
                return true;
            }
        }
        return false;
    }

    auto insert_new_question(int from, int to, string question)
    {
        // generate new id for new question
        int new_id = gen_question_id();

        // store in DataBase
        bool is_stored = db.add_new_question_line(new_id, from, to, question);

        if (!is_stored)
        {
            qIDs.erase(new_id);
            return make_pair(false, -1);
        }

        // add the new question to the server
        vector<Thread> threads;                                                 // initialize emtpy threads
        questions.push_back(Question(new_id, from, to, question, "", threads)); // add the new question to the server questions

        return make_pair(true, new_id);
    }

    bool delete_parent_question(const int &question_index)
    {
        int q_id = questions[question_index].ID;

        vector<int> thrd_ids;     // a copy for thread ids of parent question
        thrd_ids.push_back(q_id); // push the question id to the list

        if (!db.delete_question_line(q_id)) // remove from the database
            return false;

        // remove from server
        for (auto &thread : questions[question_index].threads) // collect all thread ids to free them
            thrd_ids.push_back(thread.ID);

        // Erase question
        auto it = questions.begin();
        it += question_index;
        questions.erase(it);

        // free the ids
        for (auto &i : thrd_ids)
        {
            auto id_it = qIDs.find(i);
            qIDs.erase(id_it);
        }

        return true;
    }

    bool delete_thread_question(const int &question_index, const int &thread_index)
    {
        int parent_question_id = questions[question_index].ID;
        int thread_question_id = questions[question_index].threads[thread_index].ID;
        // delete from the database
        if (!db.delete_thread(parent_question_id, thread_question_id))
            return false;

        // delete from the server
        questions[question_index].delete_thread(thread_index); // delete thread question

        // free id for deleted thread
        auto id_it = qIDs.find(thread_question_id);
        qIDs.erase(id_it);

        return true;
    }

    bool delete_question(const int &question_id)
    {
        vector<int> ids;

        // iterate over all questions and threads
        int sz = questions.size();
        for (int i = 0; i < sz; i++)
        {
            if (questions[i].ID == question_id) // if id for a parent question
            {
                if (!delete_parent_question(i))
                {
                    cout << "Can't delete the question." << endl;
                    return false;
                }
                else
                    return true;
            }

            // if id for thread question
            int t_sz = questions[i].threads.size();
            for (int j = 0; j < t_sz; j++)
            {
                if (!delete_thread_question(i, j)) // if id for a thread question
                {
                    cout << "Can't delete the thread" << endl;
                    return false;
                }
                else
                    return true;
            }
        }
        cout << "Error: unable to extract question from id." << endl;
        return false;
    }
};

struct User
{
    User_Info info;
    vector<Question> sent_questions;
    vector<Question> received_questions;

    User() {}
    User(User_Info u, vector<Question> sent_q, vector<Question> received_q) : info(u), sent_questions(sent_q), received_questions(received_q) {}

    Question get_recieved_question_by_id(const int &id)
    {
        for (auto &q : received_questions)
        {
            if (q.ID == id)
                return q;

            for (auto &t : q.threads)
            {
                if (t.ID == id)
                    return q;
            }
        }
        return Question();
    }

    bool delete_recieved_question(const int &qid)
    {
        // iterate over all questions and threads
        int sz = received_questions.size();
        for (int i = 0; i < sz; i++)
        {
            if (received_questions[i].ID == qid) // if id for a parent question
            {
                auto it = received_questions.begin();
                it += i;
                received_questions.erase(it);
                return true;
            }

            int t_sz = received_questions[i].threads.size();
            for (int j = 0; j < t_sz; j++)
            {
                if (received_questions[i].threads[j].ID == qid) // if id for thread question
                {
                    received_questions[i].delete_thread(j);
                    return true;
                }
            }
        }
        cout << "Error: unable to extract question from id." << endl;
        return false;
    }

    bool answer(const string &ans, const int &qid)
    {
        // iterate over the questions
        for (auto &recieved_q : received_questions)
        {
            if (recieved_q.ID == qid)
            {
                recieved_q.answer = ans;
                return true;
            }

            // iterate over the threads of a question
            for (auto &thrd : recieved_q.threads)
            {
                if (thrd.ID == qid)
                {
                    thrd.answer = ans;
                    return true;
                }
            }
        }
        cout << "Erorr: can not find the question in the recieved list." << endl;
        return false;
    }

    void send_new_question(const int &reciever_id, const int &question_id, const string &question)
    {
        vector<Thread> empty_threads; // initialize empty vector of threads

        // hide user
        int user_id = info.user_id;
        if (info.AQ)
            user_id = -1;
        sent_questions.push_back(Question(question_id, user_id, reciever_id, question, "", empty_threads));
    }

    void send_new_thread(const int &thread_id, const int &parent_question_id, const string &question)
    {
        for (auto &q : sent_questions)
        {
            if (q.ID == parent_question_id)
            {
                // hide user
                int uid = info.user_id;
                if (info.AQ)
                    uid = -1;

                q.threads.push_back(Thread(thread_id, uid, question, ""));
                return;
            }
        }
        cout << "Error: no sent question has this id." << endl;
    }
};

struct System
{
    Server s;
    User u;
    Handling h;

    void login_Menu()
    {
        while (1) // infinte loop
        {
            // display Login Menu
            cout << "Login Menu:\n\t1: Login\n\t2: Sign Up\n";

            // prompt choice from user
            char choice[1]{0};
            while (1) // loop until choice is valid
            {
                // prompet choice from user and hundle invalid input
                bool valid = false;
                while (!valid)
                {
                    cout << "Enter your choice: ";
                    cin.getline(choice, 2);

                    if (cin.fail())
                    {
                        cout << "Error: invalid input\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else // user input no more than a one character digit
                    {
                        valid = true;
                    }
                }

                switch (choice[0])
                {
                case 49:
                {
                    while (1) // loop until user entered a valid username and password
                    {
                        // prompt user name and password
                        string uname, passwd;
                        cout << "Enter username and password (separated by a space): ";
                        cin >> uname;
                        cin.ignore();
                        getline(cin, passwd);

                        // check if username and password are valid
                        auto [is_valid_uname_and_passwd, user_info] = s.authentication(uname, passwd);

                        if (!is_valid_uname_and_passwd)
                        {
                            cout << "Erorr: Invalid username or password, please try again\n";
                            continue;
                        }

                        vector<Question> sent_questions;
                        vector<Question> recieved_questions;
                        s.get_sent_recieved_questions(user_info.user_id, sent_questions, recieved_questions);
                        u = User(user_info, sent_questions, recieved_questions); // load user data
                        cout << "Login successfully.\n";
                        main_menu();
                        break;
                    }
                    break;
                }
                case 50:
                {
                    // user sign up and prompt to login menu again
                    signup();
                    break;
                }
                default:
                {
                    cout << "Error: invalid input" << endl;
                    continue;
                }
                }
                break;
            }
        }
    }

    void signup()
    {
        string u_name{""}, passwd, name, email;
        bool AQ;

        while (1) // loop until unique username entered
        {
            while (1) // loop until valid input entered
            {
                char buffer[16]{0};
                cout << "Enter username. (no spaces): ";
                cin.getline(buffer, 16);

                try
                {
                    h.hundle_word<16>(buffer);
                }
                catch (const invalid_argument &e)
                {
                    cout << e.what();
                    if (buffer[0] != 0)                    // buffer is not empty
                        memset(buffer, 0, sizeof(buffer)); // set buffer
                    continue;
                }
                catch (const length_error &e)
                {
                    cout << e.what();
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    memset(buffer, 0, sizeof(buffer)); // set buffer
                    continue;
                }
                catch (...)
                {
                }
                // copy buffer into u_name
                for (auto &i : buffer)
                    if (i != 0)
                        u_name += i;
                    else
                        break;

                break;
            }

            if (s.check_user_name(u_name))
                break;

            cout << "Error: username already in use, please enter another username.\n";
        }
        // prompt and hundle the password
        while (1)
        {
            cout << "Enter password: ";
            getline(cin, passwd);

            if (passwd.empty())
                continue;

            break;
        }
        // prompt and hundle the name
        while (1)
        {
            cout << "Enter name: ";
            getline(cin, name);

            if (name.empty())
                continue;

            break;
        }
        // prompt and hundle the email
        while (1) // loop until valid input entered
        {
            char buffer[24]{0};
            cout << "Enter email: ";
            cin.getline(buffer, 24);

            try
            {
                h.hundle_email<24>(buffer);
            }
            catch (const invalid_argument &e)
            {
                cout << e.what();
                if (buffer[0] != 0)                    // buffer is not empty
                    memset(buffer, 0, sizeof(buffer)); // set buffer
                continue;
            }
            catch (const length_error &e)
            {
                cout << e.what();
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                memset(buffer, 0, sizeof(buffer)); // set buffer
                continue;
            }
            catch (...)
            {
            }
            // copy buffer into email
            for (auto &i : buffer)
                if (i != 0)
                    email += i;
                else
                    break;

            break;
        }
        // prompt and hundle the AQ configuration
        bool is_invalid_input = true;
        while (is_invalid_input)
        {
            cout << "Allow annonmus questions. (0 or 1): ";
            cin >> AQ;
            if (cin.fail())
            {
                cout << "Error: invalid input, please enter 0 or 1.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else
                is_invalid_input = false;
        }

        // store input data
        auto user_tuple = make_tuple(u_name, passwd, name, email, AQ);

        if (s.add_user(user_tuple))
        {
            cout << "successfully sign up, now prompet to login menu" << endl;
            return;
        }

        cout << "signup failed.\n";
    }

    void main_menu()
    {
        while (1)
        {
            cout << "Main Menu:\n"
                 << "\t1: Print Questions To Me\n"
                 << "\t2: Print Questions From Me\n"
                 << "\t3: Answer Question\n"
                 << "\t4: Delete Question\n"
                 << "\t5: Ask Question\n"
                 << "\t6: List System Users\n"
                 << "\t7: feed\n"
                 << "\t8: logout\n";

            int choice;
            cout << "Enter Number from list: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                print_questions_to_me();
                break;
            }

            case 2:
            {
                print_questions_from_me();
                break;
            }

            case 3:
            {
                answer_question();
                break;
            }
            case 4:
            {
                delete_question();
                break;
            }

            case 5:
            {
                ask_question();
                break;
            }

            case 6:
            {
                list_system_users();
                break;
            }

            case 7:
            {
                feed();
                break;
            }

            case 8:
            {
                cout << "Logout, You will prompt back to login Menu." << endl;
                break;
            }
            default:
                cout << "Erorr: invalid Namber! Please choose from list." << endl;
            }
            if (choice == 8) // choice is logout
            {
                break;
            }
        }
    }

    void print_questions_to_me()
    {
        // iterate over recieved_questions and print them
        for (auto &q : u.received_questions)
        {
            q.print();
            cout << endl;
        }
    }

    void print_questions_from_me()
    {
        // iterate over sent_questions and print them
        for (auto &q : u.sent_questions)
        {
            q.print_without_thread();
            if (q.answer == "")
                cout << "not answered yet\n";
            cout << endl;
        }
    }

    void answer_question()
    {
        int qid;
        cout << "Enter Question id or -1 to cencel: ";
        cin >> qid;

        if (qid == -1)
            return;

        Question q = u.get_recieved_question_by_id(qid);

        if (q.ID == -1)
        {
            cout << "Error: There is no revcieved question has ID (" << qid << ")." << endl;
            return;
        }

        if (q.ID == qid)
        {
            q.print_without_thread();
            cout << "\n";

            if (q.answer != "")
                cout << "note: Already answered. Answer will be apdated." << endl;
        }

        else
        {
            for (auto &t : q.threads)
            {
                if (t.ID == qid)
                {
                    cout << "parent question:\n";
                    q.print_without_thread();
                    t.print();
                    cout << "\n";

                    if (t.answer != "")
                        cout << "note: Already answered. Answer will be updated." << endl;
                }
            }
        }

        // prompt answer
        string answer{""};
        cout << "Enter Answer: ";
        cin.ignore();
        while (1)
        {
            getline(cin, answer);
            if (answer.empty())
            {
                cout << "Error: answer can't be empty, please enter your answer again: ";
                continue;
            }
            break;
        }

        if (!u.answer(answer, qid)) // local answering
            return;

        if (!s.answer_question(answer, qid)) // global answering
            cout << "Erorr: Answer does not updated globally\n";
    }

    void delete_question()
    {
        int qid{0};
        cout << "Enter Question ID: ";
        cin >> qid;

        auto q = u.get_recieved_question_by_id(qid);
        if (q.ID == -1)
        {
            cout << "Error: There is no recieved question has the same id." << endl;
            return;
        }

        if (!s.delete_question(qid))
            cout << "question is not deleted globally." << endl;

        if (!u.delete_recieved_question(qid))
            cout << "question is not deleted locally." << endl;
    }

    void ask_question()
    {
        int to_uid;
        cout << "Enter user id or -1 to cencel: ";
        cin >> to_uid;

        if (!s.is_valid_user_id(to_uid))
        {
            cout << "Invalid user id" << endl;
            return;
        }

        int qid;
        cout << "For thread question: Enter question id or -1 for new question: ";
        cin >> qid;
        cout << " Enter Question text: ";
        string question;
        cin.ignore();
        while (1)
        {
            getline(cin, question);
            if (question.empty())
            {
                cout << "Error: question can't be empty, please enter your question again: ";
                continue;
            }
            break;
        }

        if (qid == -1) // if new parent question
        {
            auto [is_inserted, qid] = s.insert_new_question(u.info.user_id, to_uid, question); // add new question globally
            if (is_inserted)
                u.send_new_question(to_uid, qid, question); // add new question locally

            else
                cout << "Error: New Question is not added." << endl;

            return;
        }

        bool is_valid_qid = s.is_valid_question_id(qid);
        if (!is_valid_qid)
        {
            cout << "Erorr: Invalid question id.\n";
            return;
        }

        auto [is_inserted, tid] = s.insert_new_thread(qid, u.info.user_id, to_uid, question); // insert global thread
        if (is_inserted)
        {
            u.send_new_thread(tid, qid, question); // insert local thread
            return;
        }

        cout << "Unable to insert thread." << endl;
    }

    void list_system_users()
    {
        for (auto &usr : s.users_info)
        {
            cout << "Name: " << usr.name << "\t" << "ID: " << usr.user_id << endl;
        }
    }

    void feed()
    {
        for (int i = 0; i != -1; i++)
        {
            Question q = s.get_question_by_index(i);

            // reach end of questions
            if (q.ID == -1)
                break;

            // printing the question
            if (q.answer != "")
            {
                cout << "Question ID (" << q.ID << ")";
                if (q.from_user_id != -1)
                    cout << " from user id (" << q.from_user_id << ")";
                if (q.to_user_id != -1)
                    cout << " to user id (" << q.to_user_id << ")";
                cout << "    Question: " << q.content << endl;
                cout << " Answer: " << q.answer << endl;
                // print threads
                for (auto &thrd : q.threads)
                {
                    if (thrd.answer != "")
                    {
                        cout << "Parent Question ID (" << q.ID << ") ";
                        cout << "Question ID (" << thrd.ID << ") ";
                        if (thrd.from_user_id != -1)
                            cout << "from user id (" << thrd.from_user_id << ") ";
                        cout << "    Question: " << thrd.content << endl;
                        cout << " Answer: " << thrd.answer << endl;
                    }
                }
                cout << endl;
            }
        }
    }
};
int main()
{
    System sys;
    // sys.login_Menu();
    sys.signup();
    return 0;
}