#include<iostream>
#include<climits>
#include<math.h>
#include<vector>
using namespace std;
void build_seg_tree(vector<int>& seg_tree,vector<int>& arr,int low,int high,int pos){
    if(low==high){
        seg_tree[pos]=arr[low];
        return;
    }
    int mid=(low+high)/2;
    build_seg_tree(seg_tree,arr,low,mid,2*pos+1);
    build_seg_tree(seg_tree,arr,mid+1,high,2*pos+2);
    seg_tree[pos]=seg_tree[2*pos+1]+seg_tree[2*pos+2];
}
void range_update(vector<int>& seg_tree,vector<int>& arr,vector<int>& lazy,int qlow,int qhigh,int low,int high,int pos,int val){
    if(lazy[pos]!=0){
        seg_tree[pos]+=lazy[pos]*(high-low+1);
        if(low!=high){
            lazy[2*pos+1]+=lazy[pos];
            lazy[2*pos+2]+=lazy[pos];
        }
        lazy[pos]=0;
    }
    if(qlow>high || qhigh<low || low>high){
        return;
    }
    if(qlow<=low && high<=qhigh){
        seg_tree[pos]+=val*(high-low+1);
        if(low!=high){
            lazy[2*pos+1]+=val;
            lazy[2*pos+2]+=val;
        }
        return;
   }
    int mid=(low+high)/2;
    range_update(seg_tree,arr,lazy,qlow,qhigh,low,mid,2*pos+1,val);
    range_update(seg_tree,arr,lazy,qlow,qhigh,mid+1,high,2*pos+2,val);
    seg_tree[pos]=seg_tree[2*pos+1]+seg_tree[2*pos+2];
}
int range_query_sum(vector<int>& seg_tree,vector<int>& arr,vector<int>& lazy,int qlow,int qhigh,int low,int high,int pos){
    if(lazy[pos]!=0){
        seg_tree[pos]+=lazy[pos]*(high-low+1);
        if(low!=high){
            lazy[2*pos+1]+=lazy[pos];
            lazy[2*pos+2]+=lazy[pos];
        }
        lazy[pos]=0;
    }
    if(qlow>high || qhigh<low || low>high){
        return 0;
    }
    if(qlow<=low && high<=qhigh){
        return seg_tree[pos];
    }
    int mid=(low+high)/2;
    return range_query_sum(seg_tree,arr,lazy,qlow,qhigh,low,mid,2*pos+1)+range_query_sum(seg_tree,arr,lazy,qlow,qhigh,mid+1,high,2*pos+2);
}
int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int n1=2*n-1;
    vector<int>seg_tree(n1);
    build_seg_tree(seg_tree,arr,0,n-1,0);
    cout<<"Segment Tree : "<<endl;
    for(int i=0;i<n1;i++){
        cout<<seg_tree[i]<<" ";
    }
    cout<<endl;
    int l,r,val;
    cin>>l;
    cin>>r;
    cin>>val;
    vector<int>lazy(n1);
    range_update(seg_tree,arr,lazy,l,r,0,n-1,0,val);
    cout<<"Enter the range query at which sum is to be calculated: ";
    cin>>l;
    cin>>r;
    int range_sum=range_query_sum(seg_tree,arr,lazy,l,r,0,n-1,0);
    cout<<"Range query sum after Range updation : ";
    cout<<range_sum;
    cout<<endl;
    return 0;
}