public class L033 {

    public static class ListNode {
        int val;
        ListNode next;

        ListNode(int val) {
            this.val = val;
            this.next = null;
        }
    }

    public static class LinkedList {

        ListNode head;
        ListNode tail;
        int len;

        LinkedList() {
            this.head = null;
            this.tail = null;
            this.len = 0;
        }

        public int size() {
            return this.len;
        }

        public boolean isEmpty() {
            return this.len == 0;
        }

        @Override
        public String toString() {
            String str = "";
            ListNode cur = head;
            while (cur != null) {
                str += (cur.val + "->");
                cur = cur.next;
            }
            return str;
        }

        public ListNode getNode(int pos) {
            if (pos >= len) {
                return new ListNode(-1);
            }
            ListNode cur = head;
            int i = 0;
            while (i != pos) {
                cur = cur.next;
                i++;
            }
            return cur;

        }

        // adding element===========================================================

        public void addFirst(int data) {

            this.len++;
            ListNode node = new ListNode(data);

            if (head == null) { // empty list
                head = node;
                tail = node;
                return;
            }

            node.next = head;
            head = node;
            return;

        }

        public void addLast(int data) {

            this.len++;
            ListNode node = new ListNode(data);

            if (head == null) { // empty list
                head = node;
                tail = node;
                return;
            }

            tail.next = node;
            tail = node;
            return;
        }

        public void addAt(int data, int pos) {

            if (pos < 0 || pos > len)
                return;

            if (pos == 0) {
                addFirst(data);
            } else if (pos == len) {
                addLast(data);
            } else {
                ListNode prev = getNode(pos - 1);
                ListNode forward = prev.next;
                ListNode middle = new ListNode(data);
                prev.next = middle;
                middle.next = forward;
                this.len++;
            }
            return;

        }

        // removing element
        public int removeFirst() {
            if (head == null) {
                return -1;
            }

            ListNode remove = head;
            head = head.next;
            remove.next = null;
            this.len--;

            return remove.val;
        }

        public int removeLast() {
            if (head == null) {
                return -1;
            }
            if (head == tail) {
                int ans = head.val;
                head = null;
                tail = null;
                this.len--;
                return ans;
            }
            ListNode secondLast = getNode(this.len - 2);
            ListNode remove = tail;
            secondLast.next = null;
            this.len--;
            tail = secondLast;

            return remove.val;
        }

        public int removeAt(int pos) {
            if (head == null || pos < 0 || pos > this.len - 1) {
                return -1;
            }

            if (pos == 0) {
                return this.removeFirst();
            } else if (pos == this.len - 1) {
                return this.removeLast();
            } else {
                ListNode secondLast = getNode(pos - 1);
                ListNode remove = secondLast.next;
                secondLast.next = remove.next;
                remove.next = null;
                this.len--;
                return remove.val;
            }
        }
    }

    public static LinkedList reverseLL(LinkedList ll) {

        if (ll.head == null || ll.head.next == null)
            return ll;

        ListNode prev = null, cur = ll.head, forward = ll.head.next;
        while (cur != null) {
            cur.next = prev;
            prev = cur;
            cur = forward;
            if (forward != null)
                forward = forward.next;
        }
        ll.tail = ll.head;
        ll.head = prev;
        return ll;
    }

    public static void removeFirst(ListNode head) {

    }

    public static void removeLast(ListNode head) {
        if (head == null || head.next == null)
            return;

        ListNode temp = head;
        while (temp.next.next != null) {
            temp = temp.next;
        }
        temp.next = null;
    }

    public static void removeNode(ListNode head, ListNode cur) {
        if (head == null)
            return;
        ListNode temp = head;
        while (temp.next != cur) {
            temp = temp.next;
        }
        temp.next = cur.next;
        cur.next = null;
    }

    public static ListNode removeElements(ListNode head, int data) {
        if (head == null)
            return null;
        if (head.next == null && head.val != data)
            return head;

        ListNode cur = head;

        while (cur != null) {

            ListNode forward = cur.next;

            if (cur.val == data) {
                if (cur == head) { // first element
                    removeFirst(head);
                    ListNode temp = head;
                    head = head.next;
                    temp.next = null;
                } else if (cur.next == null) { // last element
                    removeLast(head);
                } else { // in middle
                    removeNode(head, cur);
                }
            }

            cur = forward;
        }
        return head;
    }

    public static ListNode oddEven_byValue(ListNode head) {
        if (head == null || head.next == null)
            return head;

        ListNode prev = null;
        ListNode cur = head;
        ListNode dummy = new ListNode(-1);
        ListNode track = dummy;

        while (cur != null) {
            ListNode forward = cur.next;

            if ((cur.val % 2) == 0) {
                prev = cur;
                cur = forward;
                continue;
            }
            
            //adding the cur node in the new list
            ListNode temp = cur;

            if (cur == head) {
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

            prev.next = forward;
            cur = forward;
        }

        track.next = head;  //removing the dummmy node
        ListNode temp = dummy;
        dummy = dummy.next;
        temp.next = null;

        return dummy;
    }

    public static void main(String[] args) {

        LinkedList p = new LinkedList();
        // System.out.println(p.removeFirst();

        p.addLast(10);
        p.addLast(1);
        p.addLast(1);
        p.addLast(410);
        p.addLast(1);
        p.addLast(61);
        p.addLast(51);
        p.addLast(71);
        p.addLast(81);
        p.addLast(61);
        p.addLast(90);
        System.out.println(p);
        p.head = oddEven(p.head);
        System.out.println(p);

    }

}