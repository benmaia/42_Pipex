# 42_Pipex
 
 <div align="center"><br>
  <img src="https://user-images.githubusercontent.com/76601369/110706242-77158d00-81ef-11eb-8085-5da6f0988553.jpg" alt="https://user-images.githubusercontent.com/76601369/110706242-77158d00-81ef-11eb-8085-5da6f0988553.jpg" width="650" height="300">
</div>
</br>

> *Discover in detail a UNIX mechanism, coding Pipes, Redirections and Appends and Heredoc!*

<p> This project is a recreation of pipes, redirections and appends with here_docs</p>
<p> The mandatory just recreates redirections and 2 commands, and bonus recreate redirections, multiple commands, and appends.</p> 
<p> To use it:</p>

```bash
git@github.com:benmaia/42_Pipex.git
```

```bash
cd pipex
```
<p> You have to call the program like this:</p>
<p><code> ./build/bin/pipex file1 cmd1 ... cmd3 file2</code></p>
<p> And works like:</p>
<p><code> < file 1 cmd1 | cmd2 | cmd3 > file2</code></p>
<p> To run the append use it like:</p>
<p><code> ./build/bin/pipex here_doc LIMITER cmd1 ... cmd3 file2</code></p>
<p> It recreates:</p>
<p><code> cmd1 << LIMITER | cmd2 | cmd3 >> file2</code></p>
<p> I've prepared some use cases already, you can run</p>


```bash
make mandatory //./build/bin/pipex main.txt "/bin/ls" "wc" test.txt
make bonus1 // ./build/bin/pipex main.txt "ls -l" "grep .txt" "grep test" test.txt
make bonus2 // ./build/bin/pipex main.txt "ls -l" "grep .txt" "grep test" "wc -l" test.txt
make bonus3 // ./build/bin/pipex here_doc 42 "cat" "cat" test.txt
make bonus4 // ./build/bin/pipex here_doc 42 "ls -l" "grep .txt" "grep main" test.txt
make bonus5 // ./build/bin/pipex here_doc Oi "ls -l" "cat" "grep .txt" test2.txt
```

<p> Here is an example:</p>

<img src="https://media.discordapp.net/attachments/461563270411714561/963193901198508093/Screen_Shot_2022-04-11_at_10.48.01_PM.png?width=1858&height=360" width="1000px" height="450px"/>
</br>
<p> Pipex OK ✅ Pipex Bonus OK ✅</p>
</br>
<p> Grade: 125% </p>
<div style="display: inline"><br>
   <img src="https://cdn.discordapp.com/attachments/461563270411714561/953326133233991700/Screen_Shot_2022-03-15_at_4.16.20_PM.png">
</div>
