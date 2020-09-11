public class questions {
    public static void main(String[] args) {
        return;
    }

    // leetcode 206
    class Solution {
        public ListNode getMid(ListNode head) {
            if (head == null || head.next == null)
                return head;

            ListNode slow = head, fast = head;
            while (fast != null && fast.next != null && fast.next.next != null) {
                slow = slow.next;
                fast = fast.next.next;
            }
            return slow;
        }

        public ListNode reverseLL(ListNode head) {

            if (head == null || head.next == null)
                return head;

            ListNode prev = null, cur = head, forward = head.next;
            while (cur != null) {
                cur.next = prev;
                prev = cur;
                cur = forward;
                if (forward != null)
                    forward = forward.next;
            }
            return prev;
        }

        public ListNode reverseList(ListNode head) {
            if (head == null || head.next == null)
                return head;

            ListNode mid = getMid(head);
            ListNode secondHead = mid.next;
            mid.next = null;

            secondHead = reverseLL(secondHead);
            ListNode cur1 = head;
            ListNode cur2 = secondHead;
            while (cur1 != null && cur2 != null) {
                int temp = cur2.val;
                cur2.val = cur1.val;
                cur1.val = temp;

                cur1 = cur1.next;
                cur2 = cur2.next;
            }
            secondHead = reverseLL(secondHead);
            mid.next = secondHead;
            return head;
        }
    }

    // leetcode 234
    class Solution {
        public ListNode getMid(ListNode head) {
            if (head == null || head.next == null)
                return head;

            ListNode slow = head, fast = head;
            while (fast != null && fast.next != null && fast.next.next != null) {
                slow = slow.next;
                fast = fast.next.next;
            }
            return slow;
        }

        public ListNode reverseLL(ListNode head) {

            if (head == null || head.next == null)
                return head;

            ListNode prev = null, cur = head, forward = head.next;
            while (cur != null) {
                cur.next = prev;
                prev = cur;
                cur = forward;
                if (forward != null)
                    forward = forward.next;
            }
            return prev;
        }

        public boolean isPalindrome(ListNode head) {

            if (head == null || head.next == null)
                return true;

            ListNode mid = getMid(head);
            ListNode secondHead = mid.next;
            mid.next = null;

            secondHead = reverseLL(secondHead);
            ListNode cur1 = head;
            ListNode cur2 = secondHead;
            while (cur1 != null && cur2 != null) {
                if (cur1.val != cur2.val)
                    return false;

                cur1 = cur1.next;
                cur2 = cur2.next;
            }
            return true;
        }
    }

    // leetcode 203
    class Solution {
        public ListNode removeElements(ListNode head, int data) {
            if (head == null || head.next == null) {
                if (head == null)
                    return null;
                return head.val == data ? null : head;
            }

            ListNode prev = null;
            ListNode cur = head;
            while (cur != null) {
                ListNode forward = cur.next;
                if (cur.val != data) // value not found toh aage badh jao
                {
                    prev = cur;
                    cur = forward;
                    continue;
                }
                if (cur == head) // value found at head so move head
                {
                    head.next = null;
                    head = forward;
                    cur = forward;
                    continue;
                }
                // value found in middle node, prev would have been set by now
                cur.next = null;
                prev.next = forward;
                cur = forward;
            }

            return head;

        }
    }

    // delete n nodes after m nodes
    class Solution {

        public static void linkdelete(Node head, int M, int N) {
            // your code here
            if (head == null)
                return;

            Node dummy = new Node(-1);
            dummy.next = head;

            Node slow = dummy;
            Node fast = dummy.next;

            while (fast != null) {

                int m = M;
                int n = N;

                while (m-- > 0 && fast != null) {
                    slow = slow.next;
                    fast = fast.next;
                }

                while (n-- > 0 && fast != null) {
                    fast = fast.next;
                }

                slow.next = fast;

            }

            head = dummy.next;
            dummy.next = null;
            return;
        }
    }

    // reorder list lc 143
    class Solution {

        public ListNode getMid(ListNode head) {
            if (head == null || head.next == null)
                return head;

            ListNode slow = head, fast = head;
            while (fast != null && fast.next != null && fast.next.next != null) {
                slow = slow.next;
                fast = fast.next.next;
            }
            return slow;
        }

        public ListNode reverseLL(ListNode head) {

            if (head == null || head.next == null)
                return head;

            ListNode prev = null, cur = head, forward = head.next;
            while (cur != null) {
                cur.next = prev;
                prev = cur;
                cur = forward;
                if (forward != null)
                    forward = forward.next;
            }
            return prev;
        }

        public void reorderList(ListNode head) {
            if (head == null || head.next == null || head.next.next == null)
                return;

            ListNode mid = getMid(head);
            ListNode nhead = mid.next;
            mid.next = null;
            nhead = reverseLL(nhead);

            ListNode cur1 = head;
            ListNode cur2 = nhead;

            while (cur1 != null && cur2 != null) {
                ListNode temp1 = cur1.next;
                ListNode temp2 = cur2.next;

                cur1.next = cur2;
                cur2.next = temp1;

                cur1 = temp1;
                cur2 = temp2;
            }

        }
    }

    // 328 odd even linked list
    class Solution {
        public ListNode oddEvenList(ListNode head) {
            if (head == null || head.next == null || head.next.next == null)
                return head;

            ListNode secondHead = head.next, odd = head, even = secondHead;

            while (odd.next != null && even.next != null) {
                odd.next = even.next;
                odd = odd.next;

                even.next = odd.next;
                even = even.next;
            }

            odd.next = secondHead;
            return head;
        }
    }

    // partition list by values of a node
    public ListNode oddEven_byValue(ListNode head) {
        if (head == null || head.next == null)
            return head;

        ListNode prev = null;
        ListNode cur = head;
        ListNode dummy = new ListNode(-1);
        ListNode track = dummy;

        while (cur != null) {

            //store the next , it helps
            ListNode forward = cur.next;

            //if even , let it be in the original list
            if ((cur.val % 2) == 0) {
                prev = cur;
                cur = forward;
                continue;
            }

            // mark the cur node , to append it in the other list
            ListNode temp = cur;

            if (cur == head) 
            {
                //remove from this node and add it in the other list maintained by 'track'
                head = head.next;
                temp.next = null;
                track.next = temp;
                track = temp;

                cur = forward;
                continue;
            }

            temp.next = null;
            track.next = temp;
            track = temp;

            prev.next = forward;//deleting the node
            cur = forward;
        }

        track.next = head;  //join 2 seperate lists
        ListNode del = dummy;
        dummy = dummy.next;
        del.next = null;//removing dummy

        return dummy;
    }

    // remove duplicates-1 , lc:83
    class Solution {
        public ListNode deleteDuplicates(ListNode head) {
            if (head == null || head.next == null)
                return head;
            ListNode cur = head;
            while (cur != null && cur.next != null) {
                ListNode temp = cur.next;
                while (temp != null && temp.val == cur.val)
                    temp = temp.next;
                cur.next = temp;
                cur = cur.next;
            }
            return head;
        }
    }

    // remove duplicates-2 , lc:82
    class Solution {
        public ListNode deleteDuplicates(ListNode head) {
            if (head == null || head.next == null)
                return head;

            ListNode dummy = new ListNode(-1);
            dummy.next = head;
            ListNode prev = dummy;
            ListNode cur = head;

            while (cur != null && cur.next != null) {
                //if i come at the last node,that means it has no duplicates so we dont need to process it. 
                //thts why, (cur.next!=null)
                ListNode temp = cur.next;
                if (cur.val != temp.val) {
                    prev = cur;
                    cur = temp;
                    continue;
                }
                
                //if the next of the cur is same, so go till the different element is found
                while (temp != null && temp.val == cur.val)
                    temp = temp.next;
                
                prev.next = temp;
                cur = temp;
            }

            ListNode del = dummy;
            dummy = dummy.next;
            del.next = null;
            return dummy;
        }
    }

    // lc 2: add two numbers
    class Solution {
        public void addCarry(ListNode head) {
            ListNode cur = head;
            int carry = 1;
            ListNode prev = null;
            while (cur != null && carry != 0) {
                prev = cur;
                int sum = cur.val + carry;

                if (sum >= 10) {
                    cur.val = sum % 10;
                    carry = 1;
                } else {
                    cur.val = sum;
                    carry = 0;
                }

                cur = cur.next;
            }
            if (carry == 0)
                return;
            ListNode extra = new ListNode(1);
            prev.next = extra;
            extra.next = null;
            return;
        }

        public ListNode addTwoNumbers(ListNode l1, ListNode l2) {

            if (l1 == null || l2 == null)
                return (l1 == null) ? l2 : l1;

            ListNode cur1 = l1, cur2 = l2;

            int carry = 0;
            // add and store the result in l1

            ListNode prev1 = null, prev2 = null;

            while (cur1 != null && cur2 != null) {

                //they'll be used when either list ends to append the carry
                prev1 = cur1;
                prev2 = cur2;

                int sum = cur1.val + cur2.val + carry;

                if (sum >= 10) {
                    cur1.val = sum % 10;
                    carry = 1;
                } else {
                    cur1.val = sum;
                    carry = 0;
                }

                cur1 = cur1.next;
                cur2 = cur2.next;
            }

            if (carry == 1) 
            {
                if (cur1 == null && cur2 == null) {
                    ListNode extra = new ListNode(1);
                    prev1.next = extra;
                    extra.next = null;
                } 
                else if (cur1 == null) {
                    addCarry(cur2);
                    prev1.next = cur2;
                } 
                else
                    addCarry(cur1);
            } 
            else if (cur1 == null && cur2 != null)//the answer containing list ends , so join them
                prev1.next = cur2;

            return l1;

        }
    }

    // lc : 24:=========================================
    class Solution {
        public ListNode swapPairs(ListNode head) {
            if (head == null || head.next == null)
                return head;

            ListNode dummy = new ListNode(-1);
            ListNode prev = dummy;
            dummy.next = head;
            ListNode st = head, ed = head.next;

            while (st != null && ed != null) {
                ListNode forward = ed.next;
                st.next = forward;
                ed.next = st;
                prev.next = ed;

                prev = st;
                st = forward;
                if (st != null)
                    ed = st.next;
                else
                    ed = null;
            }

            ListNode del = dummy;
            dummy = dummy.next;
            del.next = null;
            return dummy;

        }
    }

    // IMPORTANT
    // leetcode : 25 .====================================================
    class Solution {

        ListNode oh = null;
        ListNode ot = null;
        ListNode th = null;
        ListNode tt = null;

        public void addFirst(ListNode cur) {
            if (th == null) {
                th = cur;
                tt = cur;
                return;
            }
            cur.next = th;
            th = cur;
            return;
        }

        public ListNode reverseIT(ListNode hd) {
            if (hd == null || hd.next == null)
                return hd;
            ListNode prev = null;
            ListNode cur = hd;
            while (cur != null) {
                ListNode forward = cur.next;
                cur.next = prev;
                prev = cur;
                cur = forward;
            }
            return prev;
        }

        public ListNode reverseKGroup(ListNode head, int k) {
            if (head == null || head.next == null || k == 1)
                return head;
            int K = k;
            ListNode cur = head;

            while (cur != null) {
                while (cur != null && K-- > 0) {
                    ListNode forward = cur.next;
                    cur.next = null;
                    addFirst(cur);
                    cur = forward;
                }

                if (K > 0) { // when list ends(cur becomes null) but the K is not zero , reverse back the incomplete portion.
                    th = reverseIT(th);
                    ot.next = th;
                    continue; // as cur is null now, outer while loop wont run, return oh;
                }

                if (oh == null) {
                    oh = th;
                    ot = tt;
                } else {
                    ot.next = th;
                    ot = tt;
                }
                th = null;
                tt = null;
                K = k;
            }
            return oh;
        }
    }

    // leetcode 61:===============================
    // rotate list.
    class Solution {
        public ListNode rotateRight(ListNode head, int k) {
            if (head == null || head.next == null || k == 0)
                return head;

            ListNode cur = head;
            int count = 0;
            while (cur != null) {
                cur = cur.next;
                count++;
            }

            k %= count;//now k contains effective null rotations

            if (k == 0)
                return head; // effective null rotations

            ListNode slow = head;
            ListNode fast = head;

            //we'll find the point from where we have to break the list
            //1->2->3->4->5->6->7->null

            //rotate 2 times means remove last two, and append in front, use two pointer
            while (k-- > 0)
                fast = fast.next;

            while (fast.next != null) {
                slow = slow.next;
                fast = fast.next;
            }

            ListNode nhead = slow.next;
            slow.next = null;
            fast.next = head;
            head = nhead;
            return head;

        }
    }

    // plus one linked list
    public class Solution {
        public void addCarry(ListNode head) {
            if (head == null)
                return;

            ListNode cur = head;
            ListNode prev = null;
            int carry = 1;

            while (cur != null && carry != 0) {
                //whenever carry becomes zero, work is done
                ListNode forward = cur.next;
                int sum = carry + cur.val;
                
                if (sum < 10) {
                    carry = 0;
                    cur.val = sum;
                } else {
                    carry = 1;
                    cur.val = sum % 10;//basically zero
                }

                prev = cur;
                cur = forward;
            }

            //case of (9->9->9->null), add one, it will become (0->0->0->1)
            if (carry == 1) {
                ListNode extra = new ListNode(1);
                prev.next = extra;
                extra.next = null;
            }
            return;
        }

        public ListNode reverseLL(ListNode head) {
            if (head == null || head.next == null)
                return head;

            ListNode prev = null;
            ListNode cur = head;

            while (cur != null) {
                ListNode forward = cur.next;

                cur.next = prev;
                prev = cur;
                cur = forward;
            }

            return prev;

        }

        public ListNode plusOne(ListNode head) {
            // Write your code here
            if (head == null)
                return head;
            head = reverseLL(head);
            addCarry(head);
            return head = reverseLL(head);

        }
    }
}