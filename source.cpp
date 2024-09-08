#include <iostream>
#include <tuple>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>
using namespace std;

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

    auto get_user_line_by_user_name(const std::string &user_name)
    {
        pair<bool, tuple<int, string, string, string, string, bool>> output = make_pair(0, make_tuple(-1, "", "", "", "", 0));
        read.open(users_path);

        if (read.fail())
        {
            cout << "Error: can't open file. " << endl;
            return output;
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
                return output;
            }

            output = make_pair(true, make_tuple(attr1, attr2_uname, attr3, attr4, attr5, attr6));
            break;
        }

        read.close();
        return output;
    }

    // questions manipulation functions
    bool add_new_question_line(tuple<int, int, int, string> new_data)
    {
        auto &[id, from, to, question] = new_data;
        string ans{""};
        int t_num = 0;

        write.open(questions_path);
        if (write.fail())
        {
            cout << "Error: can't open file.\n";
            return false;
        }

        write << id << "," << from << "," << to << "," << question << "," << ans << "," << t_num << endl;

        if (write.fail())
        {
            cout << "Error: error in writing on file.\n";
            return false;
        }

        write.close();
        return true;
    }

    bool store_new_thread(const int &line_num, tuple<int, int, string, string> thrd)
    {
        // logic of updating question
        return true;
    }

    bool update_question_line(tuple<int, int, int, string, string, vector<tuple<int, int, string, string>>> modifyed_line)
    {
        // logic of updating question
        return true;
    }

    bool delete_question_line(const int & id)
    {
        // logic of deleting
        return true;
    }

    bool delete_thread(const int& parent_q_id, const int& thrd_id)
    {
        //logic of deleting thread
        return true;
    }
};

struct User_Info
{
    int user_id = -1;
    string user_name = "";
    string password = "";
    string name = "";
    string email = "";
    bool AQ = false;

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
    int ID;
    int from_user_id;
    string content;
    string answer;

    Thread(int id, int from, string content, string answer) : ID(id), from_user_id(from), content(content), answer(answer) {}
    void print()
    {
        cout << "Thread ID: " << ID << "\t";
        if (from_user_id != -1)
            cout << "From User ID: " << from_user_id << "\t";
        cout << "Question: " << content << endl;
        if (answer != "")
            cout << "Answer: " << answer << endl;
    }
};

struct Question
{
    int ID = -1;
    int from_user_id = -1;
    int to_user_id = -1;
    string content = "";
    string answer = "";
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
            cout << "From User ID: " << from_user_id << "\t";
        cout << "To User ID: " << to_user_id << "\t";
        cout << "Question: " << content << endl;
        if (answer != "")
            cout << "Answer: " << answer << endl;
        if (threads.size())
        {
            cout << "Threads: " << endl;
            for (auto &thrd : threads)
            {
                thrd.print();
            }
        }
    }

    void print_without_thread()
    {
        cout << "Question ID: " << ID << "\t";
        if (from_user_id != -1)
            cout << "From User ID: " << from_user_id << "\t";
        cout << "To User ID: " << to_user_id << "\t";
        cout << "Question: " << content << endl;
        if (answer != "")
            cout << "Answer: " << answer << endl;
    }

    void new_thread(const Thread &thrd)
    {
        threads.push_back(thrd);
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
        }
    }

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

    bool check_user_name(const string &user_name)
    {
        auto [it, is_inserted] = user_names.insert(user_name);
        if (is_inserted)
            return 1;
        return 0;
    }

    bool add_user(tuple<string, string, string, string, bool> &info)
    {
        int new_id = gen_user_id();
        auto new_record = tuple_cat(make_tuple(new_id), info);

        if (!db.store_user(new_record))
            return false;

        push_back_user_info(new_record);

        return true;
    }

    void push_back_user_info(tuple<int, string, string, string, string, bool> &record)
    {
        users_info.push_back(User_Info(record));
    }

    pair<bool, User_Info> authentication(const string &user_name, const string &password)
    {
        // return is_authenticated, matched_user_info
        pair<bool, tuple<int, string, string, string, string, bool>> info = db.get_user_line_by_user_name(user_name);
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

    bool new_thread(const int &qid, const Thread &thrd)
    {
        int i = get_question_index(qid);

        if(!db.store_new_thread(i, make_tuple(thrd.ID, thrd.from_user_id, thrd.content, "")));
            return false;
        
        questions[i].new_thread(thrd);
        return true;
    }

    bool answer(const string &ans, const int &qid)
    {
        for (auto &q : questions)
        {
            if (q.ID == qid)
            {
                q.answer = ans;

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

    bool get_sent_recieved_questions(int uid, vector<Question> &sent, vector<Question> &recieved)
    {
        bool is_vaild_uid = uIDs.count(uid);
        if (!is_vaild_uid)
            return false;

        int sz = questions.size();
        for (int i = 0; i < sz; i++)
        {
            Question q = questions[i];
            if (q.from_user_id == uid)
            {
                sent.push_back(q);
            }
            else if (q.to_user_id == uid)
            {
                recieved.push_back(q);
            }
        }

        return true;
    }

    bool is_valid_user_id(int id)
    {
        return uIDs.count(id);
    }

    bool is_valid_question_id(int id)
    {
        return qIDs.count(id);
    }

    bool new_question(int from, int to, string question)
    {
        //generate new id for new question
        int new_id = gen_question_id();

        //store in DataBase
        tuple<int, int, int, string> new_tuple;
        bool is_stored = db.add_new_question_line(new_tuple);
        if (!is_stored)
            return false;

        //add the new question to the server
        vector<Thread> threads;//initialize emtpy threads
        questions.push_back(Question(new_id, from, to, question, "", threads));//add the new question to the server questions

        return true;
    }

    bool delete_question_by_id(int id)
    {
        int index = 0;
        vector<int> ids;
        for (auto it = questions.begin(); it != questions.end();)
        {
            if ((*it).ID == id)
            {
                // delete the question

                //from the database
                if(!db.delete_question_line(id))
                    return false;

                //from the server
                for(auto& i : (*it).threads)//collect all thread ids to free them
                    ids.push_back(i.ID);
                questions.erase(it);
                //free the ids
                for(auto& i : ids){
                    auto id_it = qIDs.find(i);
                    qIDs.erase(id_it);
                }
                
                return true;
            }

            for (auto t_it = (*it).threads.begin(); t_it != (*it).threads.end();)
            {
                if ((*t_it).ID == id)
                {
                    // delete the thread question

                    //from the database
                    if(!db.delete_thread((*it).ID, id))
                        return false;

                    //from the server
                    (*it).threads.erase(t_it);//delete question
                    //free id for new questions
                    auto id_it = qIDs.find(id);
                    qIDs.erase(id_it);
                    return true;
                }
            }
            it++;
        }
        cout << "Erorr: Cannot delete question." << endl;
        return false;
    }
};

struct User
{
    User_Info info;
    vector<Question> sent_questions;
    vector<Question> received_questions;

    User() {}
    User(User_Info u) : info(u)
    {
    }

    bool answer(const string &ans, const int &qid)
    {
        for (auto &recieved_q : received_questions)
        {
            if (recieved_q.ID == qid)
            {
                recieved_q.answer = ans;
                return true;
            }
        }
        cout << "Erorr: can not find the question in the recieved list." << endl;
        return false;
    }
};
struct System
{
    Server s;
    User u;

    void login_Menu()
    {
        while (1) // infinte loop
        {
            // display Login Menu
            cout << "Login Menu:\n\t1: Login\n\t2: Sign Up\n";

            // prompt choice from user
            short int choice;
            while (1) // loop until choice is valid
            {
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    while (1) // loop until user entered a valid username and password
                    {
                        cout << "Enter username and password: ";

                        auto [is_valid, user_info] = login();

                        if (!is_valid)
                        {
                            cout << "Erorr: Invalid username or password, please try again\n";
                            continue;
                        }

                        u = User(user_info);
                        s.get_sent_recieved_questions(u.info.user_id, u.sent_questions, u.received_questions);
                        cout << "Login successfully.\n";
                        main_menu();
                        break;
                    }
                    break;
                }
                case 2:
                {
                    // user sign up and prompt to login menu again
                    signup();
                    break;
                }
                default:
                {
                    cout << "Invalid choice, please enter number from list." << endl;
                    continue;
                }
                }
                break;
            }
        }
    }
    void signup()
    {
        string u_name, passwd, name, email;
        bool AQ;

        while (1)
        {
            cout << "Enter username. (no spaces): ";
            cin >> u_name;

            if (s.check_user_name(u_name))
                break;

            cout << "Error: username already in use, please enter another username.\n";
        }
        cout << "Enter password: ";
        cin >> passwd;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter email: ";
        cin >> email;
        cout << "Allow annonmus questions. (0 or 1): ";
        cin >> AQ;

        auto user_tuple = make_tuple(u_name, passwd, name, email, AQ);

        if (s.add_user(user_tuple))
        {
            cout << "successfully sign up, now prompet to login menu" << endl;
            return;
        }

        cout << "signup failed.\n";
    }
    pair<bool, User_Info> login()
    {
        string name, passwd;
        cin >> name >> passwd;

        return s.authentication(name, passwd);
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

            if (choice == 1)
                print_questions_to_me();
            else if (choice == 2)
                print_questions_from_me();
            else if (choice == 3)
                answer_question();
            else if (choice == 4)
                delete_question();
            else if (choice == 5)
                ask_question();
            else if (choice == 6)
                list_system_users();
            else if (choice == 7)
                feed();
            else if (choice == 8)
            {
                cout << "Logout, You will prompt back to login Menu.\n"
                     << endl;
                break;
            }
            else
                cout << "Erorr: invalid Namber! Please choose from list." << endl;
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
            q.print();
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

        Question q = s.get_question_by_id(qid);

        if (q.ID == -1)
            return;

        q.print_without_thread();
        cout << "\n";

        if (q.answer != "")
            cout << "note: Already answered. Answer will be apdated." << endl;

        string answer{""};
        cout << "Enter Answer: ";
        cin.ignore();
        getline(cin, answer);

        u.answer(answer, qid);
        s.answer(answer, qid);
    }
    void delete_question()
    {
        int qid{0};
        cout << "Enter Question ID: ";
        cin >> qid;
        if (!s.is_valid_question_id(qid))
        {
            cout << "Invalid Question ID" << endl;
            return;
        }
        s.delete_question_by_id(qid);
    }
    void ask_question()
    {
        int uid;
        cout << "Enter user id or -1 to cencel: ";
        cin >> uid;
        if (!s.is_valid_user_id(uid))
        {
            cout << "Invalid user id" << endl;
            return;
        }

        int qid;
        cout << "For thread question: Enter question id or -1 for new question: ";
        cin >> qid;

        if (qid == -1)
        {
            string question;
            cout << " Enter Question text: ";
            getline(cin, question);
            s.new_question(u.info.user_id, uid, question);
            return;
        }

        bool is_valid_qid = s.is_valid_question_id(qid);
        if (!is_valid_qid)
        {
            cout << "Erorr: Invalid question id.\n";
            return;
        }
    }
    void list_system_users()
    {
        for (auto &usr : s.users_info)
        {
            cout << "Name: " << usr.user_name << "\t" << "ID: " << usr.user_id << endl;
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
    System sys1;
    sys1.login_Menu();

    return 0;
}