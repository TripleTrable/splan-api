# splan-api

## Description

Wrapper and parser for the StarPlanner API

## Collaboration



### Working with branches

Every contributor should use his/her initials (eg. Max Mustermann uses 'mm') as
the branch prefix. After the prefix comes the issue ID and a short name
describing the work.

The branch of Max Mustermann regarding the issue "#13 Integrate Fancy UI into
the new web server" should be named:

```
mm/13-integrate-new-web-ui
```

### Pull requests

Collaboration are accepted as mail patches to the following Mail:
lars.niesen@stud.th-rosenheim.de

### Merging for thoses allowed

Merges are to be done the following:

1. Update main.
```
$ git pull origin
```
2. Rebase main onto your feature branches.
    In your feature branch do:

```
$ git rebase origin/main
```

3. Test Again if the rebase broke something.
4. Squash your commits into one.
```
$ git rebase -i HEAD~<num of commits>
```
In the now open editor replace `pick` with `squash` on all of your commits
except the first. After that quit the editor and another editor should pop up.
Now enter the new commit message. The commit message should look like this:
```
<issue id>: Description
```
For the above example it would be:
```
GL-13: Integrate the new web-UI to improve the experience for new users.
```
The Description should be **why** the commit was made and not **what** the
commit does.

As a rule of thumb, I would recommend the Glibc/kernel style commit messages as
these are even usefull without Github issues

6. Now force push your branch to the remote.

```
$ git push --force
```
7. Fast-forward merge on Github without merge commit.


For those who are not comfortable with git rebase please follow these steps. It
is still recommended to do the squashing on the terminal.


1. Update main.
```
$ git pull origin/main
```

2. Rebase main onto your feature branches.
    In your feature branch do:

```
$ git rebase origin/main
```

3. Test Again if the rebase broke something.

4. Now force push your branch to the remote.

```
$ git push --force
```

5. In the PR now fast-forward merge with squashing and without merge commit.

