#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

struct Photo {
    vector<int> id;
    char type;
    int nrTags;
    string tags[105];
};

int getInterest(Photo p1, Photo p2) {
    unordered_set<string> h1, h2;
    int ctags = 0, tags1 = 0, tags2 = 0;

    for(int i = 0; i < p1.nrTags; ++i) {
        h1.insert(p1.tags[i]);
    }

    for(int i = 0; i< p2.nrTags; ++i) {
        h2.insert(p2.tags[i]);
    }

    int minim = min(h1.size(), h2.size());

    unordered_set<string> :: iterator itr; 

    if(h1.size() == minim) {

        for (itr = h1.begin(); itr != h1.end(); itr++) {
            if (h2.find(*itr) == h2.end()) {
                tags1++;
            } 
            else {
                ctags++;
            }
        }

        tags2 = p2.nrTags - ctags;
    } else {
        for (itr = h2.begin(); itr != h2.end(); itr++) {
            if (h1.find(*itr) == h1.end()) {
                tags2++;
            } 
            else {
                ctags++;
            }
        }

        tags1 = p1.nrTags - ctags;
    }

    if(ctags <= tags1 && tags1 <= tags2) return ctags;
    if(tags1 <= ctags && ctags <= tags2) return tags1;
    
    return tags2;
    
}

int getCommonElements(Photo p1, Photo p2) {
    unordered_set<string> h1, h2;
    int ctags = 0;

    for(int i = 0; i < p1.nrTags; ++i) {
        h1.insert(p1.tags[i]);
    }

    for(int i = 0; i< p2.nrTags; ++i) {
        h2.insert(p2.tags[i]);
    }

    int minim = min(h1.size(), h2.size());

    unordered_set<string> :: iterator itr; 

    if(h1.size() == minim) {
        for (itr = h1.begin(); itr != h1.end(); itr++) {
            if (h2.find(*itr) != h2.end()) {
                ctags++;
            }
        }
    } else {
        for (itr = h2.begin(); itr != h2.end(); itr++) {
            if (h1.find(*itr) != h1.end()) {
                ctags++;
            }
        }
    }

    return ctags;
}

Photo merge(Photo p1, Photo p2) {
    Photo p;

    unordered_set<string> h;

    for(int i = 0; i < p1.nrTags; ++i) {
        h.insert(p1.tags[i]);
    }

    for(int i = 0; i< p2.nrTags; ++i) {
        h.insert(p2.tags[i]);
    }

    unordered_set<string> :: iterator itr;
    
    int count = 0;

    for (itr = h.begin(); itr != h.end(); itr++) {
        p.tags[count++] = *itr;
    }

    p.type = 'H';
    p.nrTags = count;
    p.id.push_back(p1.id[0]);
    p.id.push_back(p2.id[0]);

    return p;
}

int main() {
    int nrP;
    
    vector<Photo> hPhotos, vPhotos, slideshow;

    cin>>nrP; 

    nrP/1000;

    for(int i = 0; i < nrP; ++i) {

        Photo p;

        cin>>p.type>>p.nrTags;

        for(int j = 0; j < p.nrTags; ++j) {
            cin>>p.tags[j];
        }

        p.id.push_back(i);

        if(p.type == 'V') {
            vPhotos.push_back(p);
        } else {
            hPhotos.push_back(p);
        }
    }

    bool tagged[100001];

    for(int i = 0; i < vPhotos.size() -1; ++i) {

        int min = 10000, common, pos = -1;
        Photo bestMatch;
        
        if(tagged[i] == false) {
            for(int j = i+1; j < vPhotos.size(); ++j) if(tagged[j] == false) {
                common = getCommonElements(vPhotos[i], vPhotos[j]);

                if(common < min) {
                    min = common;
                    pos = j;
                }
            }

            if(pos != -1) {
                bestMatch = vPhotos[pos];
                tagged[pos] = true;
                tagged[i] = true;
            }
        
            Photo p_merged;
            p_merged = merge(vPhotos[i], bestMatch);
            hPhotos.push_back(p_merged);
        }
    }

    
    slideshow.push_back(hPhotos[0]);

    for(int i = 1; i < hPhotos.size(); ++i) {
        
        int maxi = getInterest(slideshow[0], hPhotos[i]);
        int pos = 0;

        if(getInterest(slideshow[i-1], hPhotos[i]) > maxi) {
            maxi = getInterest(slideshow[i-1], hPhotos[i]);
            pos = i;
        }

        for(int j = 0; j < i-1; ++j) {
            int current_interest = getInterest(slideshow[j], slideshow[j+1]);
            int potential_interest = getInterest(slideshow[j], hPhotos[i]) + getInterest(hPhotos[i], slideshow[j+1]);

            if(potential_interest > current_interest && potential_interest > maxi) {
                maxi = potential_interest;
                pos = j+1;
            }
        }

        slideshow.emplace(slideshow.begin()+pos, hPhotos[i]);
        
    }

    cout<<slideshow.size()<<'\n';

    for(int i = 0; i < slideshow.size(); ++i) {

        for(int j = 0; j < slideshow[i].id.size(); ++j) {
            cout<<slideshow[i].id[j]<<" ";
        }

        cout<<'\n';
    }

    return 0;

}
