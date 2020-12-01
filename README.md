# Extended-Process-Manager
### Operating Systems Project <br/>
### Designed and implemented an extended version of a Process Manager<br/>
 - PCB, RCB, and RL data structures<br/>
 - Functions: create(), destroy(), request(), release(), timeout(), scheduler(), init()<br/><br/>
  
### Designed and implemented a shell to process command line inputs
 - in
    - Restore the system to its initial state.
 -	cr p
    - Invoke function create(), which creates a new process at the priority level p
    - p can be 1 or 2 (0 is reserved for init process)
 -	de i
    - Invoke the function destroy(), which destroy the process identified by the PCB index i, and all of its descendants
 -	rq r n
    - Invoke the function request(), which requests n units of resource r; 
    - r can be 0, 1, 2, or 3; n=1 for r=0 and r=1, n=2 for n=2, and n=3 for n=3.
 -	rl r n
    - Invoke the function release(), which release the resource r;
    - r can be 0, 1, 2, or 3; n gives the number of units to be released
 -	to
    - Invoke the function timeout().
