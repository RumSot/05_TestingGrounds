## How to diff with LFS assets.

Unreal doesn't understand LFS so we first have to get the file pointed to under LFS using SourceTree and its terminal.

* First get the commit ID from SourceTree; its the unique number inside the square brackets.
* Using SourceTree's terminal paste the following into the git show command...
 * the commit ID
 * the path to the LFS file
 * and the output path (where we want the output file stored)

`git show (commit ID):(path to the LFS file) | git lfs smudge > (output path)`

For example using...
- Commit ID: e2a6a1e
- Path: Content/Weapons/Gun_BP.uasset
- Output path: Content/GunOld_BP.uasset

we get...

`git show e2a6a1e:Content/Weapons/Gun_BP.uasset | git lfs smudge > Content/GunOld_BP.uasset`

We next move this file into the same folder as the asset we wish to compare it with and use unreal to diff as normal.
