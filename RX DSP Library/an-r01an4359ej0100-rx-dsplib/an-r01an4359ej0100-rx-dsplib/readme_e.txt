READ ME

This READ ME file describes the configuration and contents of this folder.

 an-r01an4359jjAAAA-rx-dsplib                 Folder for storing all files and sub-folders
    |- r01an4359jjAAAA-rx-dsplib.pdf          Application note file
    |- readme_e.txt                           This file
    |- reference_document                     Folder for storing documents such as User's Manual
    |- dsplib-rxv1                            Folder containing the dsp library filess for RXv1
    |- dsplib-rxv2                            Folder containing the dsp library filess for RXv2
    |- dsplib-rxv3                            Folder containing the dsp library filess for RXv3
    |- RXv1_DSP_Sample_CCRX                   Folder containing the sample project for RXv1
    |       |- dsplib-rxv1                    Folder containing the dsp library filess for RXv1
    |       |- generate                       Source folder
    |       |- src                            Source folder
    |       |- RXv1_DSP_Sample_CCRX.rcpc      Renesas common project file
    |
    |- RXv1_DSP_Sample_CCRX                   Folder containing the sample project for RXv2
    |       |- dsplib-rxv2                    Folder containing the dsp library filess for RXv2
    |       |- generate                       Source folder
    |       |- src                            Source folder
    |       |- RXv2_DSP_Sample_CCRX.rcpc      Renesas common project file
    |
    |- RXv3_DSP_Sample_CCRX                   Folder containing the sample project for RXv3
            |- dsplib-rxv3                    Folder containing the dsp library filess for RXv3
            |- generate                       Source folder
            |- src                            Source folder
            |- RXv3_DSP_Sample_CCRX.rcpc      Renesas common project file

 AAAA: Revision, version

The project folder stores all the necessary files to import a project into the integrated development environment, i.e. the e2 studio or CS+. By using the project folder, you can easily build and debug the project without making a new project in the integrated development environment.

To use a project with the e2 studio, specify a project folder from the File >> Import menu. With CS+, import the rcpc file in the project folder.
 
Note on using the provided project:
The provided project may be unusable depending on the version of the integrated development environment, C compiler, or emulator software.
If the project is unusable, update the integrated development environment to the latest version. If you are unable to update to the latest version, create a new project and copy files in the src and the dsplib-rxv* folders to the newly created project.


