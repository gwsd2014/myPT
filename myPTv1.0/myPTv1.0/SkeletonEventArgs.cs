using Microsoft.Research.Kinect.Nui;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace myPTv1._0
{
    public class SkeletonEventArgs : EventArgs
    {
        //Array to hold all Joints
        public Joint[] Joints {get; set; }
    }
}
