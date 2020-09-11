// linked list connected components.. think from the point of view of the list.
class Solution
{
public:
    int numComponents(ListNode *head, vector<int> &G)
    {
        if (head == nullptr)
            return 0;

        unordered_set<int> map;
        for (int ele : G)
        {
            map.insert(ele);
        }

        int count = 0;
        string st
        ListNode *cur = head;
        while (cur != nullptr)
        {
            if (map.find(cur->val) != map.end())
            {
                while (cur != nullptr && map.find(cur->val) != map.end())
                    cur = cur->next;
                count++;
                continue;
            }
            //when the cur node is not there is the subset.===========
            cur = cur->next;
        }

        return count;
    }
};
