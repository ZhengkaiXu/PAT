#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "temperature.h"

using namespace std;
const long long inf = 0x3f3f3f3f3f3f;
typedef long long ll;
const int maxn = 1e5;

int cmp(const void *a, const void *b);

struct yav;

template<typename TtT>
class Vector {
private:
    TtT *Data;
    int Len, Size;
public:
    inline Vector() {
        Data = NULL;
        Len = Size = 0;
    }

    inline Vector(const Vector &other) {
        if (this == &other || !Len)return;
        Data = (TtT *) malloc(sizeof(TtT) * other.Len);
        for (int i = 0; i < other.Size; i++)Data[i] = other.Data[i];
        Len = other.Len, Size = other.Size;
    }

    inline TtT &operator[](const int x) {
        return Data[x];
    }

    const Vector &push_back(const TtT x) {
        if (Size >= Len) {
            Len = (Len == 0 ? 1 : Len << 1);
            TtT *newData = (TtT *) malloc(sizeof(TtT) * Len);
            memcpy(newData, Data, Size * sizeof(TtT));
            free(Data);
            Data = newData;
        }
        Data[Size++] = x;
        return *this;
    }

    const Vector &pop_back() {
        Size--;
        if (Size == (Len >> 2)) {
            Len = Len >> 1;
            TtT *newData = (TtT *) malloc(sizeof(TtT) * Len);
            memcpy(newData, Data, Size * sizeof(TtT));
            free(Data);
            Data = newData;
        }
        return *this;
    }

    inline unsigned int size() {
        return Size;
    }

    inline unsigned int len() {
        return Len;
    }

    inline void sort() {//用这个sort就会出错不知道为什么
        qsort(Data, Size, sizeof(TtT), cmp);
    }


};

ll answer, count;

struct yav {//y and val
    int y, val;


} bbb[maxn];

int cmp(const void *a, const void *b) {
    return (*(yav *) a).y - (*(yav *) b).y;

}


typedef struct Node {
    int BF;
    ll x, y, temperature;
    ll maxx, minx;

    Node() {
        maxx = -inf;
        minx = inf;
    }

    Vector<long long> ysorted, temp, d;
    Vector<yav> xtemp;
    struct Node *lc, *rc;
} Node, *Tree;

void LR(Tree *p) { //左旋
    Tree R;
    R = (*p)->rc;
    (*p)->rc = R->lc;
    R->lc = (*p);
    *p = R;
}

void RR(Tree *p) { //右旋
    Tree L;
    L = (*p)->lc;
    (*p)->lc = L->rc;
    L->rc = (*p);
    *p = L;
}

void LB(Tree *T) {
    Tree L, Lr;
    L = (*T)->lc;
    switch (L->BF) {
        case 1://新节点插入在T的左孩子的左子树上，做单右旋处理
            (*T)->BF = L->BF = 0;
            RR(T);
            break;
        case -1://新插入节点在T的左孩子的右子树上，做双旋处理
            Lr = L->rc;
            switch (Lr->BF) {
                case 1:
                    (*T)->BF = -1;
                    L->BF = 0;
                    break;
                case 0:
                    (*T)->BF = L->BF = 0;
                    break;
                case -1:
                    (*T)->BF = 0;
                    L->BF = 1;
                    break;
            }
            Lr->BF = 0;
            LR(&(*T)->lc);
            RR(T);
    }
}

void RB(Tree *T) {
    Tree R, Rl;
    R = (*T)->rc;
    switch (R->BF) {
        case -1://新节点插在T的右孩子的右子树上，要做单左旋处理
            (*T)->BF = R->BF = 0;
            LR(T);
            break;
        case 1://新节点插在T的右孩子的左子树上，要做双旋处理
            Rl = R->lc;
            switch (Rl->BF) {
                case 1:
                    (*T)->BF = 0;
                    R->BF = -1;
                    break;
                case 0:
                    (*T)->BF = R->BF = 0;
                    break;
                case -1:
                    (*T)->BF = 1;
                    R->BF = 0;
                    break;
            }
            Rl->BF = 0;
            RR(&(*T)->rc);
            LR(T);
    }
}

bool insert(Tree *T, int x, int y, int val, bool *taller) { //变量taller反应T长高与否
    if (!*T) {
        *T = new Node;
        (*T)->x = x;
        (*T)->y = y;
        (*T)->temperature = val;
        (*T)->lc = (*T)->rc = NULL;
        (*T)->BF = 0;
        (*T)->xtemp.push_back({y, val});

        *taller = true;
    } else {
        if (x == (*T)->x) { //不插入,将y和val加入
            *taller = false;
            (*T)->xtemp.push_back({y, val});
            return false;
        }
        if (x < (*T)->x) {
            //以下为左子树插入
            if (!insert(&(*T)->lc, x, y, val, taller))//未插入
                return false;
            if (*taller) {  //插入左子树，左子树深度增加
                switch ((*T)->BF) {
                    case 1://深度若为1，则开始调整
                        LB(T);
                        *taller = false;
                        break;
                    case 0://左右子树等深，左子树变深
                        (*T)->BF = 1;
                        *taller = true;
                        break;
                    case -1://右子树比左子树深，左右子树等深
                        (*T)->BF = 0;
                        *taller = false;
                        break;
                }
            }
        } else {
            //以下为右子树插入
            if (!insert(&(*T)->rc, x, y, val, taller))
                return false;
            if (*taller) { //插入右子树，右子树深度增加
                switch ((*T)->BF) {
                    case 1://左子树比右子树深，左右子树等深
                        (*T)->BF = 0;
                        *taller = false;
                        break;
                    case 0://左右子树等深，右子树变深
                        (*T)->BF = -1;
                        *taller = true;
                        break;
                    case -1://深度若为-1，则开始调整
                        RB(T);
                        *taller = false;
                        break;
                }
            }
        }
    }
    return true;
}

inline ll Max(ll a, ll b) {
    if (a > b) return a;
    else return b;
}

inline ll Min(ll a, ll b) {
    if (a < b) return a;
    else return b;
}

void merge1(Tree *T, int l, int mid, int r) {
    if (l == r) return;
    merge1(&(*T), l, (l + mid) >> 1, mid);
    merge1(&(*T), mid + 1, (mid + 1 + r) >> 1, r);
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (j > r || (i <= mid && (*T)->xtemp[i].y < (*T)->xtemp[j].y)) bbb[k] = (*T)->xtemp[i++];
        else bbb[k] = (*T)->xtemp[j++];
    }
    for (int k = l; k <= r; k++)
        (*T)->xtemp[k] = bbb[k];
}

void build(Tree *T) {
    if ((*T) == NULL) return;

    build(&((*T)->lc));
    build(&((*T)->rc));


    (*T)->maxx = (*T)->x;
    (*T)->minx = (*T)->x;
    if ((*T)->lc != NULL) {
        (*T)->maxx = Max((*T)->maxx, (*T)->lc->maxx);
        (*T)->minx = Min((*T)->minx, (*T)->lc->minx);
    }
    if ((*T)->rc != NULL) {
        (*T)->maxx = Max((*T)->maxx, (*T)->rc->maxx);
        (*T)->minx = Min((*T)->minx, (*T)->rc->minx);
    }
    //调用这个sort排序就会出问题，所以后来手写了个归并
    // (*T)->xtemp.sort();
    int too = (*T)->xtemp.size() - 1;
    merge1(&(*T), 0, too / 2, too);
    Vector<long long> ytemp, valtemp;
    int lsize = 0, rsize = 0, tsize = 0;
    if ((*T)->lc != NULL)
        lsize = (*T)->lc->ysorted.size() - 1;
    if ((*T)->rc != NULL)
        rsize = (*T)->rc->ysorted.size() - 1;
    tsize = (*T)->xtemp.size();
    int nowt, nowl, nowr;
    nowt = 0, nowl = 1;
    while (nowt < tsize && nowl < lsize) {
        if ((*T)->lc->ysorted[nowl] < (*T)->xtemp[nowt].y) {
            ytemp.push_back((*T)->lc->ysorted[nowl]);
            valtemp.push_back((*T)->lc->temp[nowl++]);
        } else {
            ytemp.push_back((*T)->xtemp[nowt].y);
            valtemp.push_back((*T)->xtemp[nowt++].val);
        }
    }
    while (nowt < tsize) {
        ytemp.push_back((*T)->xtemp[nowt].y);
        valtemp.push_back((*T)->xtemp[nowt++].val);
    }
    while (nowl < lsize) {
        ytemp.push_back((*T)->lc->ysorted[nowl]);
        valtemp.push_back((*T)->lc->temp[nowl++]);
    }


    int to = ytemp.size();
    nowr = 1, nowt = 0;
    (*T)->ysorted.push_back(-inf);
    (*T)->temp.push_back(0);
    while (nowr < rsize && nowt < to) {
        if ((*T)->rc->ysorted[nowr] < ytemp[nowt]) {
            (*T)->ysorted.push_back((*T)->rc->ysorted[nowr]);
            (*T)->temp.push_back((*T)->rc->temp[nowr++]);
        } else {
            (*T)->ysorted.push_back(ytemp[nowt]);
            (*T)->temp.push_back(valtemp[nowt++]);
        }
    }
    while (nowr < rsize) {
        (*T)->ysorted.push_back((*T)->rc->ysorted[nowr]);
        (*T)->temp.push_back((*T)->rc->temp[nowr++]);
    }
    while (nowt < to) {
        (*T)->ysorted.push_back(ytemp[nowt]);
        (*T)->temp.push_back(valtemp[nowt++]);
    }


    to = (*T)->ysorted.size();
    (*T)->ysorted.push_back(inf);
    (*T)->temp.push_back(0);
    (*T)->d.push_back(0);
    for (int i = 1; i < to; i++) {
        (*T)->d.push_back((*T)->d[i - 1] + (*T)->temp[i]);
    }
}

void slove(Tree *T, int y1, int y2) {
    int l = 0, r = (*T)->ysorted.size() - 1;
    if ((*T)->ysorted[1] > y2 || (*T)->ysorted[r - 1] < y1) return;

    int mid;
    int from, to;
    while (l < r) {
        mid = (l + r + 1) >> 1;
        if ((*T)->ysorted[mid] >= y1) r = mid - 1;
        else l = mid;
    }
    from = l;

    l = 0, r = (*T)->ysorted.size() - 1;
    while (l < r) {
        mid = (l + r) >> 1;
        if ((*T)->ysorted[mid] <= y2) l = mid + 1;
        else r = mid;
    }
    to = l;
    count = count + to - from - 1;
    answer = answer + (*T)->d[to - 1] - (*T)->d[from];
}

void slove2(Tree *T, int y1, int y2) {
    for (int i = 0; i < (*T)->xtemp.size(); i++) {
        if ((*T)->xtemp[i].y >= y1 && (*T)->xtemp[i].y <= y2) {
            answer += (*T)->xtemp[i].val;
            count++;
        }
    }
}

void query(Tree *T, int x1, int y1, int x2, int y2) {
    if ((*T) == NULL) return;
    if ((*T)->minx >= x1 && (*T)->maxx <= x2) {
        slove(&(*T), y1, y2);
        return;
    }
    if ((*T)->maxx < x1 || (*T)->minx > x2) return;
    if ((*T)->x >= x1 && (*T)->x <= x2) {
        slove2(&(*T), y1, y2);
    }
    query(&(*T)->lc, x1, y1, x2, y2);
    query(&(*T)->rc, x1, y1, x2, y2);
}


int main() {
    //freopen("in.txt", "r", stdin);
    int n, q;
    n = GetNumOfStation();
    int x, y, val;
    Tree T = NULL;
    bool taller;
    for (int i = 0; i < n; i++) {
        GetStationInfo(i, &x, &y, &val);
        insert(&T, x, y, val, &taller);
    }
    build(&T);
    int x1, y1, x2, y2;
    while (GetQuery(&x1, &y1, &x2, &y2)) {
        answer = 0, count = 0;
        query(&T, x1, y1, x2, y2);
        if (count == 0) {
            Response(0);
        } else {
            Response(answer / count);
        }
    }
    return 0;
}