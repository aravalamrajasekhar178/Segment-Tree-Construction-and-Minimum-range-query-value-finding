#include<iostream>
#include<climits>
#include<math.h>
#include<vector>
using namespace std;
void range_query_sum(vector<int>& arr,vector<int>& seg_tree,int low,int high,int pos){
    if(low==high){
        seg_tree[pos]=arr[low];
        return;
    }
    int mid=(low+high)/2;
    range_query_sum(arr,seg_tree,low,mid,2*pos+1);
    range_query_sum(arr,seg_tree,mid+1,high,2*pos+2);
    seg_tree[pos]=seg_tree[2*pos+1]+seg_tree[2*pos+2];
}
void update_points(vector<int>& arr,vector<int>& seg_tree,int low,int high,int idx,int val,int pos){
    if(idx<low || idx>high){
        return;
    }
    if(low==high){
        seg_tree[pos]+=val;
        return;
    }
    int mid=(low+high)/2;
    if(low<=idx && idx<=mid){
        update_points(arr,seg_tree,low,mid,idx,val,2*pos+1);
    }else if(mid+1<=idx && idx<=high){
        update_points(arr,seg_tree,mid+1,high,idx,val,2*pos+2);
    }
    seg_tree[pos]=seg_tree[2*pos+1]+seg_tree[2*pos+2];
    
}
int search_range_sum_query(vector<int>& arr,vector<int>& seg_tree,int low,int high,int qlow,int qhigh,int pos){
    if(qlow<=low && high<=qhigh){
        return seg_tree[pos];
    }
    if(qlow>high || low>qhigh){
        return 0;
    }
    int mid=(low+high)/2;
    return search_range_sum_query(arr,seg_tree,low,mid,qlow,qhigh,2*pos+1)+search_range_sum_query(arr,seg_tree,mid+1,high,qlow,qhigh,2*pos+2);
}

int main(){
    cout<<"Enter Array Size : ";
    int n;
    cin>>n;
    vector<int> arr(n);
    cout<<"Enter Array Elements : ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int n1=2*n-1;
    vector<int> seg_tree(n1,INT_MAX);
    range_query_sum(arr,seg_tree,0,n-1,0);
    for(int i=0;i<n1;i++){
        cout<<seg_tree[i]<<" ";
    }
    cout<<endl;
    int idx,val;
    cout<<"Enter the index and the value to update at the given index"<<endl;
    cin>>idx;
    cin>>val;
    update_points(arr,seg_tree,0,n-1,idx,val,0);
    cout<<"Segment Tree after point update : "<<endl;
    for(int i=0;i<n1;i++){
        cout<<seg_tree[i]<<" ";
    }
    cout<<endl;
    cout<<"Enter the query range to calculate the sum at that particular range"<<endl;
    int l,r;
    cin>>l;
    cin>>r;
    cout<<"The sum in the given range query : ";
    int range_sum=search_range_sum_query(arr,seg_tree,0,n-1,l,r,0);
    cout<<range_sum<<endl;
    return 0;
}