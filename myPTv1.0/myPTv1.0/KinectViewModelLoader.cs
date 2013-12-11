using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

//Mike Hodnick
//kindohm
namespace myPTv1._0
{
    public class KinectViewModelLoader
    {
        static FlexionExtensionViewModel flexionExtensionViewModelStatic;
        static IkinectService kinectRuntime;

         public KinectViewModelLoader()
        {
            kinectRuntime = new KinectRuntime();

            var prop = DesignerProperties.IsInDesignModeProperty;
            var isInDesignMode =
                (bool)DependencyPropertyDescriptor
                .FromProperty(prop, typeof(FrameworkElement))
                .Metadata.DefaultValue;

            if (!isInDesignMode)
            {
                kinectRuntime.Initialize();
            }
        }

        public static FlexionExtensionViewModel FlexionExtensionViewModelStatic
        {
            get
            {
                if (flexionExtensionViewModelStatic == null)
                {
                    flexionExtensionViewModelStatic = new FlexionExtensionViewModel(kinectRuntime);
                }
                return flexionExtensionViewModelStatic;
            }
        }

        public FlexionExtensionViewModel FlexionExtensionViewModel
        {
            get
            {
                return flexionExtensionViewModelStatic;
            }
        }

        public static void Cleanup()
        {
            if (flexionExtensionViewModelStatic != null)
            {
                flexionExtensionViewModelStatic.Cleanup();
            }

            kinectRuntime.Cleanup();
        }
    }
}
