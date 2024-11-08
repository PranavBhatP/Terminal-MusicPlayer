#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include <cctype>
#include <random>
#include <chrono>
#include <thread>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

struct Node {
    string data;
    Node* next;
    Node* prev;
};

Node* head = nullptr;
Node* current_node = nullptr;
vector<Node*> playlist;
sf::Music music;
bool isPaused = false;

string toLower(const string& str) {
    string lowerStr;
    transform(str.begin(), str.end(), back_inserter(lowerStr), [](char c){ return tolower(c); });
    return lowerStr;
}

void loadSongs() {
    string path = "./music";
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ".mp3") {
            string songName = entry.path().filename().string();
            Node* new_node = new Node{entry.path().string(), nullptr, nullptr};
            if (!head) {
                new_node->next = new_node->prev = new_node;
                head = current_node = new_node;
            } else {
                Node* last = head->prev;
                new_node->prev = last;
                last->next = new_node;
                new_node->next = head;
                head->prev = new_node;
            }
            playlist.push_back(new_node);
        } else {
            cout << "Non-mp3 songs are present! Please ensure all the songs are MP3 format!!\n";
        }
    }
}

void playSong(const string& songPath) {
    if (music.openFromFile(songPath)) {
        music.play();
        cout << "Now playing: " << songPath << "\n";
    } else {
        cout << "Error: Cannot play " << songPath << "\n";
    }
}

void togglePause() {
    if (music.getStatus() == sf::Music::Playing) {
        music.pause();
        isPaused = true;
        cout << "Music paused.\n";
    } else if (isPaused) {
        music.play();
        isPaused = false;
        cout << "Music resumed.\n";
    }
}

void nextNode() {
    if (!current_node) {
        cout << "Playlist is empty.\n";
        return;
    }
    current_node = current_node->next;
    playSong(current_node->data);
}

void prevNode() {
    if (!current_node) {
        cout << "Playlist is empty.\n";
        return;
    }
    current_node = current_node->prev;
    playSong(current_node->data);
}

void shufflePlaylist() {
    if (playlist.empty()) {
        cout << "Playlist is empty.\n";
        return;
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(playlist.begin(), playlist.end(), g);

    for (size_t i = 0; i < playlist.size(); i++) {
        playlist[i]->next = playlist[(i + 1) % playlist.size()];
        playlist[i]->prev = playlist[(i - 1 + playlist.size()) % playlist.size()];
    }
    head = playlist.front();
    current_node = head;
    cout << "Playlist shuffled.\n";
}

void specificSong(const string& songName) {
    if (!head) {
        cout << "No music in playlist.\n";
        return;
    }
    Node* ptr = head;
    do {
        if (toLower(ptr->data).find(toLower(songName)) != string::npos) {
            current_node = ptr;
            playSong(current_node->data);
            return;
        }
        ptr = ptr->next;
    } while (ptr != head);
    cout << "Song not found.\n";
}

void show() {
    if (!head) {
        cout << "Playlist is empty.\n";
        return;
    }
    Node* show_ptr = head;
    int i = 1;
    cout << "\nPlaylist:\n";
    do {
        cout << i++ << ". " << show_ptr->data << "\n";
        show_ptr = show_ptr->next;
    } while (show_ptr != head);
}

bool reorderPlaylist(const vector<int>& order) {
    vector<Node*> newOrder;
    set<int> seen;
    
    for (int idx : order) {
        if (idx < 1 || idx > playlist.size() || seen.count(idx)) {
            cout << "Invalid order entry: " << idx << ". Please ensure entries are within the range and unique.\n";
            return false;
        }
        newOrder.push_back(playlist[idx - 1]);
        seen.insert(idx);
    }

    for (size_t i = 0; i < newOrder.size(); ++i) {
        newOrder[i]->next = newOrder[(i + 1) % newOrder.size()];
        newOrder[i]->prev = newOrder[(i - 1 + newOrder.size()) % newOrder.size()];
    }
    head = newOrder.front();
    current_node = head;
    cout << "Playlist reordered.\n";
    return true;
}

void enterOrder() {
    show();
    cout << "Enter the new order of songs by index, separated by spaces:\n";
    string input;
    getline(cin, input);
    istringstream stream(input);
    vector<int> order;
    int index;

    while (stream >> index) {
        order.push_back(index);
    }

    if (order.size() != playlist.size()) {
        cout << "Error: Please enter exactly " << playlist.size() << " unique indices.\n";
        return;
    }

    if (!reorderPlaylist(order)) {
        cout << "Invalid order input. Please try again.\n";
    }
}

int main() {
    loadSongs();
    int choice;
    cout<<"Welcome to the music player on the terminal. Get started!\n";
    while (true) {
        if (music.getStatus() == sf::Music::Stopped && !isPaused && current_node) {
            nextNode(); 
        }

        cout << "\n1. Play Next Song\n";
        cout << "2. Play Previous Song\n";
        cout << "3. Show Playlist\n";
        cout << "4. Shuffle Playlist\n";
        cout << "5. Pause/Resume\n";
        cout << "6. Play Specific Song\n";
        cout << "7. Enter Playback Order\n";
        cout << "8. Exit\n";
        cin >> choice;
        cin.ignore();

        if (choice == 1) nextNode();
        else if (choice == 2) prevNode();
        else if (choice == 3) show();
        else if (choice == 4) shufflePlaylist();
        else if (choice == 5) togglePause();
        else if (choice == 6) {
            string songName;
            cout << "Enter song name: ";
            getline(cin, songName);
            specificSong(songName);
        }
        else if (choice == 7) enterOrder();
        else if (choice == 8) break;

        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
