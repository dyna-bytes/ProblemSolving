`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// BOJ problem 10828 스택
//////////////////////////////////////////////////////////////////////////////////


module stack();

    
    integer fd = 32'h8000_0000;
    integer ret;
    integer N, num, STACK[$];
    string cmd;

    initial begin
        //fd = $fopen("input.txt", "r");
        
        $fscanf(fd, "%d", N);
        while (N--) begin
            $fscanf(fd, "%s", cmd);
            if (cmd == "push") begin
                $fscanf(fd, "%d", num);
                STACK.insert(0, num);
            end
            else if (cmd == "pop") begin
                if (STACK.size() == 0) $display("-1");
                else begin
                    $display("%0d", STACK[0]);
                    STACK.delete(0);
                end            
            end
            else if (cmd == "top") begin
                if (STACK.size() == 0) $display("-1");
                else                   $display("%0d", STACK[0]);
            end
            else if (cmd == "size")
                $display("%0d", STACK.size());
            else if (cmd == "empty")
                $display("%0d", STACK.size() == 0);
        end

        //$fclose(fd);
        $finish;
    end

endmodule
