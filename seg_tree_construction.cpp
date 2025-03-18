//Space Complexity : O(n)

// For Searching Time Complexity : O(log(n))

#include<iostream>
#include<vector>
#include<math.h>
#include<climits>
using namespace std;
void construct_segment_tree(vector<int> &seg_tree,vector<int> &arr,int low,int high,int pos){
    if(low==high){
        // If low==high, then assign the value at current index 'low' to the segment tree position
        seg_tree[pos]=arr[low];
        return;
    }
    int mid=(low+high)/2;
    //Splitting into left and right child nodes
    construct_segment_tree(seg_tree,arr,low,mid,2*pos+1);
    construct_segment_tree(seg_tree,arr,mid+1,high,2*pos+2);
    seg_tree[pos]=min(seg_tree[2*pos+1],seg_tree[2*pos+2]);
}
int min_range_queries(vector<int>& seg_tree,int qlow,int qhigh,int low,int high){
    if(qlow<=low && high<=qhigh){
        // Total overlapping case,here value at low is to be returned
        return seg_tree[low];
        }
    if(qlow>high || qhigh<low){
        // No overlapping case,here INT_MAX is to be returned
        return INT_MAX;
    }
    
    //Partial Overlapping case
    int mid=(low+high)/2;
    //Searching in left and right child nodes and returning the minimum value by comparing left and right part
    return min(min_range_queries(seg_tree,qlow,qhigh,low,mid),min_range_queries(seg_tree,qlow,qhigh,mid+1,high));
}
int main(){
    cout<<"Enter the size of the Array\n";
    int n;
    cin>>n;
    vector<int> arr(n);
    cout<<"Enter Array Elements\n";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int x=(int)(ceil(log2(n)));
    int n1=(int)(2*pow(2,x)-1);
    vector<int>seg_tree(n1,INT_MAX);
    construct_segment_tree(seg_tree,arr,0,n-1,0);
    cout<<"Segment Tree of the above Array\n";
    for(int i=0;i<n1;i++){
        cout<<seg_tree[i]<<' ';
    }
    cout<<endl;
    cout<<"Enter the range query to find the minimum value ib the given range\n";
    int l,r;
    cin>>l;
    cin>>r;
    cout<<"The Minimum value in the given range is\t";
    int ans=min_range_queries(seg_tree,l,r,0,n);
    cout<<ans<<endl;
}