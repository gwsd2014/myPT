using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//Mike Hodnick
//kindohm on github
namespace myPTv1._0
{
    public interface IkinectService
    {
        void Initialize();
        void Cleanup();
        event EventHandler<SkeletonEventArgs> SkeletonUpdated;
    }
}
